#include <u.h>
#include <libc.h>
#include <stdio.h>

/* pointer version */

void
main(int argc, char *argv[])
{
	while(--argc > 0)
		/* also, use expr for first arg of printf */
		printf((argc > 1) ? "%s " : "%s", *++argv);
	printf("\n");

	exits(0);
}
