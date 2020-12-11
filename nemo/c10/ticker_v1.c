#include <u.h>
#include <libc.h>

/* this program is supposed to be something like a computer
 * input terminal that broadcasts messages to a lot of devices,
 * like an emergency broadcast system or the flights list at an
 * airport.
 *
 * there's a single 'reader' process to read messages from stdin and
 * send them off.  meanwhile, a bunch of 'panel' processes are receiving
 * incoming messages.  global memory is allocated for a single message
 * in this example with concurrency mechanisms (queue locks) setup
 * such that all the processes 'send' and 'recv' to and from the
 * same memory location, although we could imagine various other
 * transports and concurrency mechanisms, depending on the situation.
 */


enum { Npanels = 2 };

typedef struct Msg Msg;
struct Msg {
	QLock lck;
	char *text;
	ulong vers;
};

Msg msg;
int exiting;

void
reader(void)
{
	char buf[512];
	int nr;
	for(;;) {
		nr = read(0, buf, sizeof(buf) - 1);
		if(nr <= 0)
			break;
		buf[nr] = '\0';
		qlock(&msg.lck);
		free(msg.text);
		msg.text = strdup(buf);
		msg.vers++;
		qunlock(&msg.lck);
	}
	exiting = 1;
	exits(nil);
}

void
panelproc(int fd)
{
	ulong lastvers = -1;

	do {
		qlock(&msg.lck);
		if(msg.text != nil && lastvers != msg.vers) {
			write(fd, msg.text, strlen(msg.text));
			lastvers = msg.vers;
		}
		qunlock(&msg.lck);
		sleep(5 * 1000);
	} while(!exiting);
	fprint(2, "panel exiting\n");
	exits(nil);
}

void
main(void)
{
	int i;

	for(i = 0; i < Npanels; i++)
		if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
			panelproc(1);
	reader();
}
