#include <u.h>
#include <libc.h>
#include <bio.h>
#include <thread.h>

/* this extended threaded ticker program extends tticker.c
 * to include a time and [simulated] temperature in each message.
 * conceptually, the novel concept is being able to fan-in channels
 * from several threads to a single thread:  tticker.c included
 * fan-out of messages in the broadcast channel to each of the panel
 * channels.  this program introduces three additional channels,
 * all of which fan-in to the broadcast channel.
 */

enum { Npanels = 2 };

Channel *timerc;
Channel *consc;
Channel *tempc;
Channel *bcastc;
Channel *panelc[Npanels];

/* the threads to fan messages out of the broadcast channel are
 * largely unchanged
 */
typedef struct PArg {
	Channel *c;
	int fd;
} PArg;

void
consreadthread(void *)
{
	Biobuf bin;
	char *ln;

	threadsetname("consread");
	Binit(&bin, 0, OREAD);
	/* along with sending to consc instead of bcastc,
	 * omitting the newline character is the only change
	 * in the fan-out threads from tticker.c
	 */
	while(ln = Brdstr(&bin, '\n', 1))
		sendp(consc, ln);
	sendp(consc, nil);
	Bterm(&bin);
	threadexits(nil);
}

void
bcastthread(void *)
{
	char *msg;
	int i;

	threadsetname("bcast");
	do {
		msg = recvp(bcastc);
		for(i = 0; i < Npanels; i++)
			if(msg != nil)
				sendp(panelc[i], strdup(msg));
			else
				sendp(panelc[i], nil);
		free(msg);
	} while(msg != nil);
	threadexits(nil);
}

void
panelthread(void *a)
{
	PArg *arg = a;
	char *msg;

	threadsetname("panel");
	while(msg = recvp(arg->c)) {
		write(arg->fd, msg, strlen(msg));
		free(msg);
	}
	threadexits(nil);
}

/* the threads to write messages to the timer and temparature channels
 * are both straightforward loops
 */

/* send a message every minute */
void
timerthread(void *a)
{
	Channel *c = a;
	ulong now;
	Tm *tm;
	char msg[10];
	for(;;) {
		now = time(nil);
		tm = localtime(now);
		seprint(msg, msg+10, "%d:%d", tm->hour, tm->min);
		sendp(c, strdup(msg));
		sleep(60 * 1000);
	}
}

/* send a message at most once a minute if there's a simulated
 * temperature change.  an actual implementation would read temperature
 * from a device represented from a file.  this implementation
 * randomly walks temperature up and down a degree at a time.
 */
void
tempthread(void *a)
{
	Channel *c = a;
	char tempf = 90;
	char temp[10];
	char last[10];

	last[0] = '\0';
	for(;;) {
		if(frand() < 0.5)
			if(frand() < 0.5)
				tempf--;
			else
				tempf++;
		seprint(temp, temp+10, "%dF", tempf);
		if(strcmp(last, temp) != 0) {
			strcpy(last, temp);
			sendp(c, strdup(temp));
		}
		sleep(60 * 1000);
	}
}

/* here we see syntax the fan-in mechanism, alt(),
 * similar to CSP styles in clojure and go.
 */

void
decoratorthread(void *)
{
	char *lcons, *ltimer, *ltemp;
	char *consmsg, *timermsg, *tempmsg;
	char *msg;
	Alt alts[] = {
	/* an Alt struct's final parameter can also be CHANSEND
	 * to wait until a channel is ready and perform a send()
	 */
		{timerc, &timermsg, CHANRCV},
		{consc, &consmsg, CHANRCV},
		{tempc, &tempmsg, CHANRCV},
	/* the list passed to alt() must always end with this nil entry
	 */
		{nil, nil, CHANEND} };

	lcons = strdup("");
	ltimer = strdup("");
	ltemp = strdup("");
	for(;;) {
		msg = nil;
		switch(alt(alts)) {
		case 0:
			msg = smprint("%s (%s %s)\n", 
				lcons, timermsg, ltemp);
			free(ltimer);
			ltimer = timermsg;
			break;
		case 1:
			if(consmsg == nil)
			/* threadexitsall() terminates all processes
			 * and threads in the program.
			 */
				threadexitsall("terminated by user");
			msg = smprint("%s (%s %s)\n", 
				consmsg, ltimer, ltemp);
			free(lcons);
			lcons = consmsg;
			break;
		case 2:
			msg = smprint("%s (%s %s)\n", 
				lcons, ltimer, tempmsg);
			free(ltemp);
			ltemp = tempmsg;
			break;
		}
		sendp(bcastc, msg);
	}
}

/* all io threads (panels and inputs) get their own processes,
 * while both the broadcast thread and the decorator thread run
 * in the same process.
 */
void
threadmain(int, char *[])
{
	int i;
	PArg *arg;

	timerc = chancreate(sizeof(char *), 0);
	consc = chancreate(sizeof(char *), 0);
	tempc = chancreate(sizeof(char *), 0);
	proccreate(timerthread, timerc, 8*1024);
	proccreate(consreadthread, consc, 16*1024);
	proccreate(tempthread, tempc, 8*1024);
	for(i = 0; i < Npanels; i++) {
		panelc[i] = chancreate(sizeof(char *), 0);
		arg = malloc(sizeof(*arg));
		arg->c = panelc[i];
		arg->fd = 1;
		proccreate(panelthread, arg, 8*1024);
	}
	bcastc = chancreate(sizeof(char *), 0);
	threadcreate(decoratorthread, nil, 8*1024);
	bcastthread(nil);
}
