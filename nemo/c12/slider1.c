#include <u.h>
#include <libc.h>
#include <thread.h>
#include <draw.h>
#include <mouse.h>

Channel *sliderc;
Image *setcol;
Image *unsetcol;

void
mousethread(void *arg)
{
	Mousectl *mctl = arg;
	Mouse m;
	int dx, val;
	for(;;) {
		recv(mctl->c, &m);
		if(m.buttons == 1) {
			do {
				dx = m.xy.x - screen->r.min.x;
				val = dx * 100 / Dx(screen->r);
				sendul(sliderc, val);
				recv(mctl->c, &m);
			} while(m.buttons == 1);
		}
	}
}

void
resizethread(void *arg)
{
	Mousectl *mctl = arg;
	for(;;) {
		recvul(mctl->resizec);
		if(getwindow(display, Refnone) < 0)
			sysfatal("getwindow: %r");
		sendul(sliderc, ~0);
	}
}

void
drawslider(int val)
{
	Rectangle setrect, unsetrect, markrect;
	int dx;

	/* Dx(), Dy() are builtins to calculate rectangle widths and heights */
	dx = Dx(screen->r) * val / 100;
	setrect = screen->r;
	unsetrect = screen->r;
	markrect = screen->r;
	setrect.max.x = setrect.min.x + dx;
	markrect.min.x = setrect.max.x;
	markrect.max.x = setrect.max.x + 2;
	unsetrect.min.x = markrect.max.x;
	draw(screen, setrect, setcol, nil, ZP);
	draw(screen, unsetrect, unsetcol, nil, ZP);
	draw(screen, markrect, display->black, nil, ZP);
	flushimage(display, 1);
/*
	print("setrect %R, unsetrect %R, markrect %R\n",
			setrect, unsetrect, markrect);
*/
}

void
sliderthread(void *)
{
	uint val, nval;
	val = ~0;
	for(;;) {
		nval = recvul(sliderc);
		if(nval != 0 && nval <= 100) {
			if(nval == val)
				continue;
			val = nval;
		}
//		print("%d\n", val);
		drawslider(val);
	}
}

Image *
myallocimage(int col) {
	return allocimage(
		display,
		Rect(0, 0, 1, 1),
		screen->chan,
		1,
		col);
}

void
threadmain(int, char *argv[])
{
	Mousectl *mctl;

	fmtinstall('R', Rfmt);
	mctl = initmouse("/dev/mouse", nil);
	if(mctl == nil)
		sysfatal("initmouse: %r");
	if(initdraw(nil, nil, argv[0]) < 0)
		sysfatal("initdraw: %r");
	setcol = myallocimage(DYellow);
	unsetcol = myallocimage(0x777777FF);
	threadcreate(resizethread, mctl, 8*1024);
	threadcreate(mousethread, mctl, 8*1024);
	sliderc = chancreate(sizeof(ulong), 0);
	threadcreate(sliderthread, sliderc, 8*1024);
	sendul(sliderc, 50);
	threadexits(nil);
}
