#include <u.h>
#include <libc.h>

/* remember, reading from cons, like most plan 9 services, technically
 * returns runes rather than bytes:  there might be more than one char
 * per rune, so the proper thing to do upon processing input is to
 * use the functions in rune(2) to operate on these hetrogenous byte
 * streams rather than hoping they'll be in homogenous byte-sized pieces.
 */

void
main(void)
{
	char buf[512];
	/* UTFmax == 3 is the maximum number of bytes per rune */
	char out[UTFmax];
	Rune r;
	int nr, irl, orl;
	char *s;
	for(;;) {
		nr = read(0, buf, sizeof(buf));
		if(nr <= 0)
			break;
		s = buf;
		while(nr > 0) {
			irl = chartorune(&r, s);
			s += irl;
			nr -= irl;
			r = toupperrune(r);
			orl = runetochar(out, &r);
			write(1, out, orl);
		}
	}
	exits(nil);
}
