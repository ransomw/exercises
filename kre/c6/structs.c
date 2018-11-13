#include <u.h>
#include <libc.h>
#include <stdio.h>
#define PRPT(P)	printf("(%d, %d)\n", P.x, P.y)

/* this is a structure declaration.
 * the keyword `struct` is followed by a name, `point`,
 * then a list of declartions in braces.
 *
 * the name, `point`, is a *structure tag* and can be used
 * as an abbreviation for the list of declarations elsewhere
 * (see below).
 *
 * the declarations in braces are *members* of the structure.
 */
struct point {
	int x;
	int y;
};

/* structure tags' and members' names don't clash with
 * other variable names.
 */
char point[] = "what again?";
int x = 1;

/* the tag is optional, and different structures can use
 * the same names for their members without conflict.
 */
struct {
	int x;
};

/* semantically, a structure declaration declares a /type/,
 * just like `int`, `char`, etc. are types.
 *
 * the `struct <name?> { ... }` declaration doesn't declare
 * a variable and no memory is allocated in the resulting
 * program based on a structure declaration. its information
 * is used by the compiler only.
 *
 * variables of any given structure type are declared
 * after the structure declaration
 */
struct {
	int x;
	int y;
	int z;
} p3a, p3b;
/* just as variables of any other type are declared */
int xa, xb;

/* structure tags are used to declare variables as follows */
struct point pta, ptb;

/* structs can be initialized at declaration with lists,
 * just like arrays --- except with one list item per member
 * and according to the members' types
 * rather than an arbitrary number of list items,
 * all of the same type.
 *
 * as with arrays, initialization with lists of constants
 * is only valid when a structure is declared.
 */
struct point maxpt = {320, 200};

/* btw, structures' members can themselves be structures */
struct rect {
	struct point a;
	struct point b;
} box;

void
main(void)
{
	/* accessing structure members (to initialize after
	 * declaration or otherwise) is possible with the
	 * structure member operator, `.`.
	 *
	 */
	pta.x = 1;
	pta.y = 2;

	PRPT(pta);
	PRPT(maxpt);
	printf("maxpt distance from origin %g\n",
		sqrt((double) maxpt.x * maxpt.x +
			(double) maxpt.y * maxpt.y));

	/* to reiterate, structures can't be initialized
	 * with lists after their initial declaration.
		ptb = {29, 31};
	 * structures /can/ be initialized by assignment
	 */
	ptb = pta;
	ptb.x = 27;
	PRPT(pta); /* (1, 2) */
	PRPT(ptb); /* (27, 2) */
	/* ^ observe that the assignment operator
	 * doesn't work by reference.  pta and ptb are
	 * stored at separate memory addressed, and the
	 * assignment above copies the values of pta to ptb.
	 */

	/* assigment initializes structs.  same as above. */
	box.a = pta;
	box.b = maxpt;
	/* btw, the member operator has the associativity
	 * you'd expect given an OOP background.
	 */
	printf("box area %d\n",
		abs((box.a.x - box.b.x) * (box.a.y - box.b.y)));


	exits(0);
}
