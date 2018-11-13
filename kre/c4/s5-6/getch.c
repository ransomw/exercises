#include <u.h> /* contains atof() */
#include <libc.h> /* contains atof() */
#include <stdio.h>
#define BUFSIZE	100 /* getch, ungetch buffer size */

/* `static` means these variables can only be accessed
 * within this file.  it may be applied to function as well as
 * variable declarations.
 * see static_vars.c regarding what static means regarding
 * internal variables (as contrasted with these external variables).
 */
static char buf[BUFSIZE];
static int bufp = 0;

int
getch(void)
{
	return bufp > 0 ?
		buf[--bufp] :
		getchar();
}

void
ungetch(int c)
{
	if(bufp >= BUFSIZE)
		exits("ungetch buffer full");
	else
		buf[bufp++] = c;
}
