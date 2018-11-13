#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * character occurance counter
 * (digits, white space, others)
 * switch statement version
 */
void
main(void)
{
	int c, i, nwhite, nother, ndigit[10];

	nwhite = nother = 0;
	for(i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while((c = getchar()) != EOF) {
		switch(c) {
		/* since cases "fall through" in the absence of
		 * a break statement --- i.e. since cases are
		 * labels only --- several cases can be attached
		 * to a single action.
		 */
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			ndigit[c-'0']++;
			/* exit the switch */
			break;
		case ' ':
		case '\n':
		case '\t':
			/* without the previous break statement,
			 * this statement would run even in the
			 * case of matching a digit character.
			 *
			 * for ease of maintainance, it's advised
			 * to use fall-throughs from one case to
			 * the next very sparingly.  multiple labels
			 * is just about the only time when
			 * fall through is desirable
			 */
			nwhite++;
			break;
		default:
			nother++;
			/* it's not necessary to have a break here.
			 * however, since the default case needn't
			 * be the last label in the switch statment,
			 * adding a break after every statement
			 * makes the program more maintainable
			 * in case more case labels are added later
			 */
			break;
		}
		/* in addition to switch statements,
		 * break statements also immediately exit
		 * while, for, and do loops
		 */
	}

	printf("digits =");
	for(i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n",
		nwhite, nother);


	exits(0);
}
