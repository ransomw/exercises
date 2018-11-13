#include <u.h>
#include <libc.h>
#include <stdio.h>

#define TAB_WIDTH	8

/******	*	*	
 ****	* test  *
 *******	*
	*	*/


void
main(void)
{
	int c, rem;

	rem = TAB_WIDTH;
	while((c = getchar()) != EOF)
		if(c == '\n') {
			putchar(c);
			rem = TAB_WIDTH;
		} else if(c == '\t') {
			for(; rem > 0; --rem)
				putchar(' ');
			rem = TAB_WIDTH;
		} else {
			putchar(c);
			--rem;
			// `%` operator not covered
			if(rem == 0)
				rem = TAB_WIDTH;
		}

	exits(0);
}
