#include <u.h>
#include <libc.h>
#include <stdio.h>

/* this introduction to pointers to structures is included
 * in sec. 6.2 on pointers and functions.
 */

struct point {
	int x;
	int y;
};

struct rect {
	struct point a;
	struct point b;
};

/* pointers to structures are frequently passed to functions
 * instead of copies of the structures themselves for reasons
 * of computational efficiency:
 * passing a structure involves allocating memory and copying
 * data while passing pointers does not.
 */

void
main(void)
{
	char s[] = "qwerty";
	/* declaring pointers to structures is another entry
	 * in the the "structure declarations declare types 
	 * just like any other type" file.
	 */
	struct point *pp;
	struct point origin = {0, 0};
	struct rect r = {{0, 0}, {0, 0}}, *rp;
	struct {
		int len;
		char *str;
	} *ssp;

	/* as usual */
	pp = &origin;
	rp = &r;
	/* precedence requires parens: `*s.m` would attempt
	 * to deref a pointer member, m, of a structure, s.
	 *
	 * i.e. -- `m` is the name of a pointer contained
	 *	in a structure named `s` in the expr `*s.m`.
	 */
	(*pp).x = 1;

	/* so there's syntatic sugar to describe derefing
	 * structures and accessing members
	 */
	pp->x += 1;
	ssp->str = s;
	ssp->len = strlen(s);

	/* compare different ways of accessing the maximum
	 * corner of a rectangle, all equivalent
	 * (except discrepancies about x or y coord)
	 */
	r.b.x = 2;
	rp->b.x += 3;
	(r.b).y = 4;
	(rp->b).y += 5;

	/* both flavors of the member operator bind
	 * tightly (as tightly as function calls and
	 * array indexing).  although parens can be
	 * used to enforce evaluation order as usual.
	 */
	--ssp->len; /* dec len */

	/*
	 * a few more notes on evaluation order, quickly
	 */

	/* access len and inc ssp afterward */
	ssp++->len;

	/* get (access) the char pointed to by str */
	*ssp->str;

	/* inc str pointer after access */

	*ssp->str++; /* like *s++ */

	/* inc (next char) str */
	(*ssp->str)++;

	/* inc ssp after accessing str */
	*ssp++->str;

	// todo: review, demonstrate use.

	exits(0);
}
