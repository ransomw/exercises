#include <u.h>
#include <libc.h>

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

/* here we slightly expand upon the async communication mechanism,
 * reading out of the shared memory segment and copying into
 * process local memory (recall rincr.c) before writing output
 * since io is slow
 */
void
panelproc(int fd)
{
	ulong lastvers = -1;
	char *text;

	do {
		text = nil;
		qlock(&msg.lck);
		if(msg.text != nil && lastvers != msg.vers) {
			text = strdup(msg.text);
			lastvers = msg.vers;
		}
		qunlock(&msg.lck);
		if(text != nil) {
			write(fd, text, strlen(text));
			free(text);
		}
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
