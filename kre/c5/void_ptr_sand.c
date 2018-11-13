#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	int x = 27;
	void *vptr;

	vptr = &x;

	printf("%d\n", *((int *)vptr) + 1);

//	printf("%d\n", *vptr);

	// todo: discuss
	/* the following are compiler errors
		*vptr + 1;
		vptr[1];
		vptr++;
	 */

	exits(0);
}
