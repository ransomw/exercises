#include <u.h>
#include <libc.h>

/* the producer-consumer or bounded-buffer problem
 * https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
 * is a classical setup closely related to implementions like Chans
 * in the kernel.  it includes a fixed-size buffer and two types
 * of processes:  producers which add items to the buffer and consumers,
 * which take items out of the buffer, FIFO.  the problem lies in
 * how to synchronize producers and consumers when the buffer is
 * full and empty, respectively.
 *
 * this implementation uses Rendez points rather than semaphores,
 * and the buffer is used in a cyclic manner.
 */

enum {Nmsgs = 4};

 /* head of queue  */
 /* tail - first empty slot */

typedef struct Buffer Buffer;
struct Buffer {
	QLock lck;
	char *msgs[Nmsgs];
	int hd;
	int tl;
	int nmsgs;
	Rendez isfull;
	Rendez isempty;
};

/* notice that the following rsleep()s and rwakeup()s are called
 * under symmetric conditions:  put() calls rwakeup(isempty)
 * precisely when get() could've possibly called rsleep(isempty).
 * if there had been a sleeping get() in this case, it's gauranteed
 * to finish running before the lock can be acquired for another put().
 * as a result, all sleeping get()s will wakeup before put() can
 * acquire the lock with nmsgs > 0.  similarly, all sleeping put()s
 * will wakup before get() will acquire the lock with nmsgs < Nmsgs.
 */

void
put(Buffer *b, char *msg)
{
	qlock(&b->lck);
	if(b->nmsgs == Nmsgs) {
		print("<full> ");
		rsleep(&b->isfull);
	}
	b->msgs[b->tl] = msg != nil ? strdup(msg) : nil;
	b->tl = ++b->tl % Nmsgs;
	b->nmsgs++;
	if(b->nmsgs == 1)
		rwakeup(&b->isempty);
	qunlock(&b->lck);
}

char *
get(Buffer *b)
{
	char *msg;

	qlock(&b->lck);
	if(b->nmsgs == 0) {
		print("<empty> ");
		rsleep(&b->isempty);
	}
	msg = b->msgs[b->hd];
	msg = msg != nil ? strdup(msg) : nil;
	b->hd = ++b->hd % Nmsgs;
	b->nmsgs--;
	if(b->nmsgs == Nmsgs - 1)
		rwakeup(&b->isfull);
	qunlock(&b->lck);
	return msg;
}

void
init(Buffer *b)
{
	/* release locks, set nils and zeros */
	memset(b, 0, sizeof(*b));
	/* both Rendez points use the same lock */
	b->isempty.l = &b->lck;
	b->isfull.l = &b->lck;
}

/**
 * process-level stuff
 *
 * for the sake of clean shutdown, there are expected to be
 * the same number of producers and consumers.  when a producer
 * finishes, it puts writes a nil message, and when a consumer
 * reads a nil message, it exits.
 */

void
producer(Buffer *b, char id)
{
	char msg[20];
	int i;

	for(i = 0; i < 5; i++) {
		seprint(msg, msg+20, "%c%d", id, i);
		put(b, msg);
	}
	put(b, nil);
	exits(nil);
}

void
consumer(Buffer *b)
{
	char *msg;

	while(msg = get(b)) {
		print("%s ", msg);
		free(msg);
	}
	exits(nil);
}

Buffer buf;

void
main(void)
{
	init(&buf);
	if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		producer(&buf, 'a');
	if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		producer(&buf, 'b');
	if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		consumer(&buf);
	else
		consumer(&buf);
}
