#include <u.h>
#include <libc.h>
#include <stdio.h>

#define TAB_WIDTH	8

/* see also c5/e11.c */
void
main(void)
{
	int c, rem, cnt;

	rem = TAB_WIDTH; // chars 'til next stop
	cnt = 0; // blanks since last stop or non-blank
	while((c = getchar()) != EOF) {
		if(c == '\n') {
			for(; cnt > 0; --cnt)
				putchar(' ');
			putchar(c);
			rem = TAB_WIDTH;
		} else if(c == ' ') {
			++cnt;
			--rem;
		} else if(c == '\t') {
			putchar(c);
			cnt = 0;
			rem = TAB_WIDTH;
		} else {
			for(; cnt > 0; --cnt)
				putchar(' ');
			putchar(c);
			--rem;
		}
		if(rem == 0) {
			if(cnt > 0) {
				putchar('\t');
				cnt = 0;
			}
			rem = TAB_WIDTH;
		}
	}

	exits(0);
}
