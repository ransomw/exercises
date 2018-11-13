#define MAXVAL	100 /* maximum number of elements on the stack */

/* notice the above #define duplicates that in stack_fns.c
 * see the following section on header files about deduping
 * this
 */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* stack of values */
