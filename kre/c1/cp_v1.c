#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * cp input to output
 * try {echo asdf | cp_v1.out} => asdf
 */
void
main(void)
{
	int c;

	c = getchar();
	while(c != EOF) {
		putchar(c); // result of operation not used
		c = getchar();
	}

	exits(0);
}
