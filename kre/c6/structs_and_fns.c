#include <u.h>
#include <libc.h>
#include <stdio.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* continuing along from structs.c */
struct point {
	int x;
	int y;
};

struct rect {
	struct point a;
	struct point b;
};

/* possible operations on a structure after declaration
 * are (strictly -- i.e. these are all possibilities)
 * - copying and assignment via `=`
 * - accessing members via `.`
 * - getting its address via `&`
 *
 * possible approaches to passing structures to and from functions
 * are (loosely)
 * - pass members separately
 * - pass an entire structure
 * - pass a pointer to a structure
 */

/* to further spell out the
 * "structure declarations declare types just like any other type"
 * motif, observe that functions can return structs or
 * take struct params (just like any other type)
 */
struct point makepoint(int, int);
struct point addpoints(struct point, struct point);
void printpoint(struct point p);


struct rect canonrect(struct rect);
int ptinrect(struct point, struct rect);

void
main(void)
{
	struct point p = {3, 4};
	/* as an aside,
	 * notice that nested lists can be used to initialize
	 * structures containing structures
	 * analogously to initializing multidimensional arrays.
	 */
	struct rect r = {{5, 5}, {2, 2}};

	printpoint(addpoints(p, makepoint(2, 5)));
	/* "constructor" functions like `makepoint` are useful
	 * because the list syntax is only legal at declaration.
	 * the following line is an error
		printpoint(addpoints(p, {1, 6}));
	 */

	/* structures are passed by value like any other type */
	printpoint(p); /* (3, 4) */

	r = canonrect(r);
	printf("%d %d\n", ptinrect(p, r),
		ptinrect(makepoint(6, 5), r));

	exits(0);
}

struct point
makepoint(int x, int y)
{
	struct point temp;

	/* note lack of naming conflicts between variable names
	 * in the current scope and names scoped by the member op.
	 * such reuse of names is common way to empahsize the
	 * relationship between the two.
	 */
	temp.x = x;
	temp.y = y;
	return temp;
}

/* continue to recall that structure tags
 * are interchangable with structure definitions,
 * and both forms can be used anywhere any of the built-in types
 * can be used, both in function return values and params.
 *
 * a notable restriction is that structure tags can be declared
 * once:  changing `anotherpoint` to `point` would be a compiler
 * error.
 */
struct anotherpoint {
	int x;
	int y;
} addpoints(struct point p, struct point q)
{
	p.x += q.x;
	p.y += q.y;
	return p;
}

void
printpoint(struct {
	int x;
	int y;
} p)
{
	printf("(%d, %d)\n", p.x, p.y);
}

/* just as "constructor" fns returning initialized structures,
 * such as makepoint are a common type of fn when working with
 * structures, so are "canonicalization" fns that are passed
 * a structure and return a structure of the same type
 * with the member variables based on the passed structures'
 * members
 */
struct rect
canonrect(struct rect r)
{
	struct rect temp;

	temp.a.x = min(r.a.x, r.b.y);
	temp.a.y = min(r.a.y, r.b.y);
	temp.b.x = max(r.a.x, r.b.y);
	temp.b.y = max(r.a.y, r.b.y);
	return temp;
}

/* slightly modified from text to
 * check if point is in a rectangle
 * or any part of its boundary
 */
int
ptinrect(struct point p, struct rect r)
{
	return p.x >= r.a.x && p.x <= r.b.x &&
		p.y >= r.a.y && p.y <= r.b.y;
}
