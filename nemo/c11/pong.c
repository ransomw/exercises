#include <u.h>
#include <libc.h>
#include <thread.h>

/* this program demonstrates unbuffered channels by sending an integer
 * value between two threads.  each thread increments and prints the
 * value before sending it back to the other thread.
 *
 * with unbuffered channels, send() and recv() calls between threads
 * have an effect similar to rendezvous() calls between processes:
 * no buffer means send() and recv() will each block until there's
 * a pair of threads calling this pair of functions with the same
 * channel.
 */

/* this channel goes from the ping thread to the pong thread */
Channel *pongc;
/* this channel goes to the ping thread, ferrying messages
 * both from the pong thread as well as an initial value from
 * the main thread
 */
Channel *pingc;

void
pingthread(void *)
{
	int msg;

	for(;;) {
		recv(pingc, &msg);
		msg++;
		print("%d\n", msg);
		send(pongc, &msg);
	}
}

void
pongthread(void *)
{
	int msg;

	for(;;) {
		recv(pongc, &msg);
		msg++;
		print("\t%d\n", msg);
		send(pingc, &msg);
	}
}

void
threadmain(int, char *[])
{
	int kickoff;

	pingc = chancreate(sizeof(int), 0);
	pongc = chancreate(sizeof(int), 0);
	threadcreate(pingthread, nil, 8*1024);
	threadcreate(pongthread, nil, 8*1024);
	kickoff = 0;
	send(pingc, &kickoff);
	threadexits(nil);
}
