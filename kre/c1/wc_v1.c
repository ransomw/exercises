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
	int c, nl, nw, nc, state;

	state = OUT;
	/* equivalently, nl = (nw = (nc = 0)); */
	nl = nw = nc = 0;
	while((c = getchar()) != EOF) {
		++nc;
		if(c == '\n')
			++nl;
		/* first use of boolean operators
		 * || means OR, && means AND.
		 * && has (just) higher precedence than ||.
		 * expressions with && and || are evaluated
		 * left-to-right.  evaluation will stop once
		 * truth or falsehood is known, */
		if(c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		/* first use of else.  general form
		 * 
	         * if (expression)
		 * 	<statement_1>
		 * else
		 * 	<statement_2>
		 *
		 * in particular, 'else if' is not a token.
		 * the 'if...' following the 'else' is a statement. */
		else if(state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);

	exits(0);
}
