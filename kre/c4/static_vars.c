#include <u.h>
#include <libc.h>
#include <stdio.h>

/* demonstrates static internal [to functions] variables.
 * for static external variables, see s5-6/getch.c
 */

int cntnext(void);

void
main(void)
{
	printf("%d %d %d\n", cntnext(), cntnext(), cntnext());
	exits(0);
}

int
cntnext(void)
{
	/* static internal variables are initialized only once
	 * rather than every time a function is called.
	 * they're initialized to zero (ch2sec4) if their
	 * declaration doesn't provide initialization.
	 */
	static int cnt;
	cnt++;
	return cnt;
}
