#include <u.h>
#include <libc.h>
#include <thread.h>
#include <draw.h>
#include <mouse.h>

/* in the same way that '#c' and/or kbdfs can be read and written
 * in order to use the keyboard, '#m' can be read and written to
 * use the mouse.  both interfaces are similarly multiplexed by rio.
 * so `cat /dev/mouse` will print mouse events that occur in a
 * particular rio window.
 *
 * the novelty of this program is not that it's about the mouse:
 * mouse(3) is analogous to kbdfs(8).
 * this program demonstrates mouse(2), the interface to use the
 * mouse from threaded programs:  recall from c11/tticker.c that
 * it's typically necessary to create separate processes to perform io
 * within threaded programs.  mouse(2) provides access to io from
 * '#m' via /dev/mouse without explicitly creating processes.
 */

void
threadmain(int, char *[])
{
	Mousectl *mctl;
	Mouse m;

	/* Pfmt is a function in draw.h to format points */
	fmtinstall('P', Pfmt);
	mctl = initmouse("/dev/mouse", nil);
	if(mctl == nil)
		sysfatal("initmouse: %r");

	/* every change of the mouse state (button up or down or move)
	 * creates a Mouse event.
	 */
	while(recv(mctl->c, &m) >= 0) {
		/* Mouse.buttons is a number 0-7 given by summing
		 * 1 - left button, 2 - middle button, 4 - right button
		 * -- i.e. the mouse button state is represented by three bits,
		 * with each bit set to 1 if the button is pressed.
		 */
		print("mouse pos=%P\tbuttons=%d\n", m.xy, m.buttons);
		if(m.buttons == 7)
			break;
	}
	closemouse(mctl);
	exits(nil);
}
