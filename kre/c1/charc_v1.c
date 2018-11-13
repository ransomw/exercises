#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * count characters 
 */
void
main(void)
{
	/* long is a minimum 32-bit int.
	 * sometimes int is 32-bit, sometimes 16-bit. */
	long nc;

	nc = 0;
	while (getchar() != EOF)
		++nc;
		/* first use of increment op.
		 * here, equivalent to nc += 1
		 * ++nc vs nc++ to be discussed later */

	/* a new printf format for long integers */
	printf("%ld\n", nc);

	exits(0);
}
