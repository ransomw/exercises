#include <u.h>
#include <libc.h>
#include <stdio.h>

#define IN	1 // inside a word
#define OUT	0 // outside a word

// todo: bio verison of this and other getchar() programs
/* count lines, words, and characters in input */
void
main(void)
{
	int state, c;

	state = OUT;
	while((c = getchar()) != EOF) {
		if(c == ' ' || c == '\n' || c == '\t') {
			if(state == IN)
				putchar('\n');
			state = OUT;
		}
		else {
			if(state == OUT)
				state = IN;
			putchar(c);
		}
	}

	exits(0);
}
