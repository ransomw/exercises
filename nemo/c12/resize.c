#include <u.h>
#include <libc.h>
#include <thread.h>
#include <draw.h>
#include <mouse.h>

/* as in blank.c */
void
blank(void)
{
	draw(screen, screen->r, display->black, nil, ZP);
	flushimage(display, 1);
}

void
mousethread(void *arg)
{
	Mousectl *mctl = arg;
	Mouse m;
	/* note that here, errors (recv() == 0) are unhandled */
	for(;;) {
		recv(mctl->c, &m);
		if(m.buttons) {
			/* a button has been pressed */
			do {
				recv(mctl->c, &m);
			} while(m.buttons);
			/* all buttons have been released.  exit the program. */
			closedisplay(display);
			closemouse(mctl);
			threadexitsall(nil);
		}
	}
}

void
resizethread(void *arg)
{
	Mousectl *mctl = arg;
	for(;;) {
		/* receiving from resizec means that the window was resized */
		recvul(mctl->resizec);
		/* getwindow() updates `screen`.
		 * it's indirectly called by initdraw().
		 * the second parameter may be among
		 * Refbackup, Refnone, Refmesg
		 * in order to describe what happens to hidden graphics
		 * when windows overlap
		 */
		if(getwindow(display, Refnone) < 0)
			sysfatal("getwindow: %r");
		blank();
	}
}

void
threadmain(int, char *argv[])
{
	Mousectl *mctl;

	mctl = initmouse("/dev/mouse", nil);
	if(mctl == nil)
		sysfatal("initmouse: %r");
	if(initdraw(nil, nil, argv[0]) < 0)
		sysfatal("initdraw: %r");
	threadcreate(resizethread, mctl, 8*1024);
	threadcreate(mousethread, mctl, 8*1024);
	blank();
	threadexits(nil);
}
