#include <u.h>
#include <libc.h>
#include <thread.h>

/* this program makes full use of the observation in pong.c about
 * blocking send() and recv() calls on unbuffered channels.
 * two identical threads running at the same time are synchronized
 * upon sending and recving messages.
 *
 * sendul() and recvul() are introduced as well.  these functions
 * are syntactic sugar for sending and receiving int-sized values
 * over channels.  similarly, sendp() and recvp() can be used for
 * pointer-sized values.
 *
 * finally, note also that there's no global Channel pointer in this
 * program.  as before, the main thread initializes the channel, and
 * this time, the channel pointer is passed to the other threads as a
 * parameter.  this underscores the fact that channels are typically
 * referred to by pointers, and chanfree() should be called if it's
 * ever necessary to reclaim the memory used by a channel.
 */

void
pingpongthread(void *a)
{
	ulong msg;
	Channel *c = a;

	for(;;) {
		msg = recvul(c);
		msg++;
		print("%d\n", msg);
		sendul(c, msg);
	}
}

void
threadmain(int, char *[])
{
	Channel *c;
	int kickoff;

	c = chancreate(sizeof(int), 0);
	threadcreate(pingpongthread, c, 8*1024);
	threadcreate(pingpongthread, c, 8*1024);
	kickoff = 0;
	sendul(c, kickoff);
	threadexits(nil);
}
