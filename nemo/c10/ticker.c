#include <u.h>
#include <libc.h>

/* behind the scenes in /sys/src/libc/9sys/qlock.c ,
 * QLocks are implemented with a linked list of rendezvous() tags,
 * QLp in libc.h.  QLock.head is the first tag in the list, and .tail
 * is the last.  qlock() and qunlock() coordinate by calling
 * rendezvous() while adding and removing tags from the list, not
 * shared-memory Locks, although changing the list of tags is protected
 * by Locks.
 *
 * Rendez wait points wrap QLocks to provide an additional list of tags.
 * rsleep() and rwakeup() add functionality to control flow that's
 * already acquired the associated QLock.  rsleep() gives up the QLock
 * and waits on a rendezvous() for a tag added to the Rendez list.
 * rwakeup() moves a tag from the Rendez list into to QLock list.
 * _since rsleep() and rwakeup() are called when the QLock is acquired_,
 * the qunlock() after rwakeup() triggers the rendezvous() at rsleep().
 */

enum { Npanels = 2 };

typedef struct Msg Msg;
struct Msg {
	QLock lck;
	Rendez newmsg;
	char *text;
};

char *
rmsg(Msg *m)
{
	char *new;

	qlock(&m->lck);
	rsleep(&m->newmsg);
	new = strdup(m->text);
	qunlock(&m->lck);
	return new;
}

void
wmsg(Msg *m, char *newtext)
{
	qlock(&m->lck);
	free(m->text);
	m->text = strdup(newtext);
	/* rwakeupall() calls rwakeup() until all Rendez tags are
	 * transferred to the QLock's tag list, so each qunlock()
	 * after an rsleep() triggers the next rsleep()'s rendezvous()
	 */
	rwakeupall(&m->newmsg);
	qunlock(&m->lck);
}

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
		wmsg(&msg, buf);
	}
	exiting = 1;
	buf[0] = '\0';
	wmsg(&msg, buf);
	exits(nil);
}

void
panelproc(int fd)
{
	char *text;

	while(!exiting) {
		text = rmsg(&msg);
		if(strlen(text) > 0)
			write(fd, text, strlen(text));
		free(text);
	};
	fprint(2, "panel exiting\n");
	exits(nil);
}

void
main(void)
{
	int i;


	/* it's super important that the QLock that's acquired
	 * during calls to rsleep() and rwakeup() is the same as
	 * that associated with the Rendez passed to these functions
	 */
	msg.newmsg.l = &msg.lck;


	for(i = 0; i < Npanels; i++)
		if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
			panelproc(1);
	reader();
}
