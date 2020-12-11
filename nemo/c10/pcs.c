#include <u.h>
#include <libc.h>

/* semaphores, like locks and rendezvous(), are sychronization tool.
 * specifically, counting semaphores are used to track how many units
 * of some given resource are available.  contrast this capability
 * with locks which generally track whether a resource is available
 * or not.  rather than lock(), semaphores are acquired with wait().
 * rather than unlock(), the number of available resources is incremented
 * with signal().
 *
 * although plan 9 doesn't provide semaphores, they can be implemented
 * with pipes.
 */

typedef struct Sem {
	int fd[2];
} Sem;

Sem *
newsem(int n) {
	Sem *s;

	s = malloc(sizeof(Sem));
	if(pipe(s->fd) < 0) {
		free(s);
		return nil;
	}
	while(n-- > 0)
		write(s->fd[1], "x", 1);
	return s;
}

void
signal(Sem *s)
{
	write(s->fd[1], "x", 1);
}

void
swait(Sem *s)
{
	char buf[1];

	read(s->fd[0], buf, 1);
}

/* semaphores can be used to implement the bounded buffer example */

enum {Nmsgs = 4};

 /* head of queue  */
 /* tail - first empty slot */

typedef struct Buffer Buffer;
struct Buffer {
	Sem *mutex; /* in place of the QLock, count of 1 */
	char *msgs[Nmsgs];
	int hd;
	int tl;
	int nmsgs;
	Sem *smsgs; /* count messages to be consumed */
	Sem *sholes; /* count available space in buffer */
};

void
init(Buffer *b)
{
	memset(b, 0, sizeof(*b));
	b->mutex = newsem(1);
	b->smsgs = newsem(0);
	b->sholes = newsem(Nmsgs);
}

void
put(Buffer *b, char *msg)
{
	swait(b->sholes);
	swait(b->mutex);
	b->msgs[b->tl] = msg != nil ? strdup(msg) : nil;
	b->tl = ++b->tl % Nmsgs;
	b->nmsgs++;
	signal(b->mutex);
	signal(b->smsgs);
}

char *
get(Buffer *b)
{
	char *msg;

	swait(b->smsgs);
	swait(b->mutex);
	msg = b->msgs[b->hd];
	msg = msg != nil ? strdup(msg) : nil;
	b->hd = ++b->hd % Nmsgs;
	b->nmsgs--;
	signal(b->mutex);
	signal(b->sholes);
	return msg;
}

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
