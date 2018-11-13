#include <u.h>
#include <libc.h>
#include <stdio.h>
#include "calc.h"
#define MAXOP	100 /* max size of operator or operand string */

void
main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			/* order that the calls to pop are
			 * evaluated isn't defined, tho for
			 * commutative operators, it doesn't matter.
			 */
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				exits("zero divisor");
			break;
		case '\n':
			printf("\t%.9g\n", pop());
			break;
		default:
			printf("error: unknown command '%s'\n", s);
			exits("unknown command");
			break;
		}
	}
	exits(0);
}
