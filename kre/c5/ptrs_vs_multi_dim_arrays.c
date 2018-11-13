#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	int xs[] = {4 /*0*/, 5/*1*/, 6/*2*/, 7/*3*/, 8/*4*/, 9};
	/* compare */
	int a[10][20];
	int *b[10];
	/* the first is a two dimensional array,
	 * the second is an array of pointers
	 */

	/* storage space has been allocated for 10*20
	 * `int`s in `a`, so it's possible to assign
	 * to that storage space.
	 */
	a[3][4] = 27;
	/* b contains allocation for 10 pointers only,
	 * so it's necessary to use separately-allocated
	 * memory space to store values
	 */
	b[3] = xs;

	/* now the same array syntax is legal to access
	 * both elements of a and b
	 */
	printf("%d %d\n", a[3][4], b[3][4]);
	/* and pointer arithmetic to first get a pointer
	 * to one index and then another produces the same
	 * value in both cases
	 */
	printf("%d %d\n",
		*(*(b + 3) + 4),
		*(*(a + 3) + 4));
	/* this pointer arithmetic is the desugared calculation
	 * of `b[3][4]`, the pointer array, *only*
	 *
	 * the index syntax applied to multi-dimensional arrays
	 * produces pointer arithmetic such as
	 */
	printf("%d\n", *(*a + (3 * 20 + 4)));
	/* i.e.
		row * <nrows> + col
	 * this calculation isn't valid for b b/c the
	 * memory for its points isn't allocated contiguously.
	 *
	 * `b + 3` calculates memory allocated to 3 pointers
	 * `a + 3` calculates memory allocated to 3
	 *	integer arrays of length 20.
	 *
	 * otoh, each pointer b[0], ..., b[9]
	 * can refer to a memory segment of a different
	 * number of `int`s, not necessary 20 `int`s.
	 */

	exits(0);
}
