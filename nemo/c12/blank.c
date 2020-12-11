#include <u.h>
#include <libc.h>
#include <draw.h>

void
main(int argc, char *argv[])
{
	Rectangle rect;
	Image *blank;

	fmtinstall('R', Rfmt);
	if(initdraw(nil, nil, argv[0]) < 0)
		sysfatal("initdraw: %r");
	/* screen is an Image */
	rect = screen->r;
	/* colors are also Images */
	blank = display->black;
	draw(
		/* destination image */
		screen,
		/* clipping rectangle: drawing occurs within this Rectangle
		 * overlaid on the destination image.
		 */
		rect,
		/* source image.  if Image.repl is set to true,
		 * draw() tiles the image to fill the clipping rectangle.
		 */
		blank,
		/* mask parameter, mainly useful for drawing cursors and
		 * other partially-transparent images.
		 */
		nil,
		/* this is a point within the source image that will
		 * be aligned within the clipping rectangle's min (top left).
		 * ZP = {0, 0} defined in draw.h performs no translation
		 */
//		Pt(rect.min.x+20, rect.min.x+20)
		ZP
	);
	flushimage(display, 1);
	sleep(3 * 1000);
	closedisplay(display);
	print("rectangle was %R\n", rect);
	exits(nil);
}
