#include <u.h>
#include <libc.h>
#include <bio.h>
#include <thread.h>

/* this program revisits the ticker programs from c10 in the context
 * of threads.
 *
 * the punchline is that it uses proccreate() instead of threadcreate().
 * proccreate() has the same sig as threadcreate(), except rather than
 * creating a new thread within the current process, it creates a new
 * threaded process beginning with the specified thread.
 * using multiple processes means that the program needn't block on io.
 * io operations block their processes only.  meanwhile, Channels can
 * communicate between threads in different processes just as they can
 * between threads in the same process, and this program requires no
 * other synchronization primitive than send() and recv() on channels.
 *
 * there's an analog of proccreate(), procrfork(), which takes
 * rfork() flags as a additional parameter.  take care *not* to pass
 * RFREND to procrfork() since libthread uses rendezvous() under the
 * hood and creating a separate rendezvous group will break its
 * functions.
 */

enum { Npanels = 2 };

/* this channel gets strings to be broadcast to all panels */
Channel *bcastc;
/* each panel gets its own channel of messages */
Channel *panelc[Npanels];

/* read messages from the console and write them to bcastc */
void
consreadthread(void *)
{
	/* recall buffered io from c3/bio*.c examples */
	Biobuf bin;
	char *ln;

	threadsetname("consread");
	Binit(&bin, 0, OREAD);
	/* c3/biocat.c used a similar Brdline, with a couple exceptions
	 * - Brdline returns a void pointer to the buffer in Biobuf
	 *   whereas Brdstr returns a freshly-allocated, null-terminated
	 *   string
	 * - Brdline can return without finding the character it's
	 *   looking for if the buffer fills up, whereas Brdstr doesn't
	 *   return until the specified character is found
	 * - Brdstr takes an additional parameter in order to include
	 *   or omit the specified character from the string.  here,
	 *   the newline character is included.
	 */
	while(ln = Brdstr(&bin, '\n', 0))
		sendp(bcastc, ln);
	sendp(bcastc, nil);
	Bterm(&bin);
	threadexits(nil);
}

/* recv messages from the broadcast channel and send them
 * to each of the panel channels.
 *
 * recall that fork() sets RFFDG|RFREND|RFPROC rfork() flags.
 * by contrast, proccreate() sets RFPROC|RFMEM|RFNOWAIT so that,
 * in particular, memory is shared across processes, so it's possible
 * to access the malloc()ated string from Brdstr in this thread and make
 * copies that'll be visible to each of the panels' threads.
 */
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

/* use structures to pass multiple parameters to threads,
 * as with the following, used as the parameter to the panel threads
 */
typedef struct PArg {
	Channel *c;
	int fd;
} PArg;

/* recv messages from a channel and write them to a file */
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

void
threadmain(int, char *[])
{
	int i;
	PArg *arg;

	bcastc = chancreate(sizeof(char *), 0);
	proccreate(consreadthread, nil, 16*1024);
	for(i = 0; i < Npanels; i++) {
		panelc[i] = chancreate(sizeof(char *), 0);
		arg = malloc(sizeof(*arg));
		arg->c = panelc[i];
		arg->fd = 1; /* panels write to stdout */
		proccreate(panelthread, arg, 8*1024);
	}
	bcastthread(nil);
}
