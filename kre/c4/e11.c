#include <u.h> /* contains atof() */
#include <libc.h> /* contains atof() */
#include <stdio.h>
#include <ctype.h> /* contains isdigit() */
#define MAXOP	100 /* max size of operator or operand string */
#define NUMBER	'0'/* signal that a number was found */
#define MAXVAL	100 /* max stack depth */
#define BUFSIZE	100 /* getch, ungetch buffer size */

/**
 * reverse-polish calculator, single-file version.
 *
 * in reverse-polish arithmetic notation,
 * operators follow operands, so
 *	(1 - 2) * (4 + 5)
 * is written as
 *	1 2 - 4 5 + *
 * a calculator for reverse-polish notation is implemented
 * here using a stack.  in pseudo-code,
while(<next operator or operand is not EOF>)
	if(<number>)
		<push>
	else if(<operator>)
		<pop operands>
		<do operation>
		<push result>
	else if(<newline>)
		<pop and print top of stack>
	else
		<error>
 */

int getop(char []);
void push(double);
double pop(void);

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

/* external variables for push and pop */

/* external variables' and functions' (which are always external --
 * functions aren't defined inside other functions) names are
 * references to the same thing, even when they're used from
 * separately-compiled files, a situation referred to as
 * 'external linkage'.
 */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* stack of values */

void
push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else {
		printf("error: stack full, cant push %g\n", f);
		exits("stack full");
	}
}

double
pop(void)
{
	if(sp > 0)
		return val[--sp];
	else {
		exits("stack empty");
		return 0.0;
	}
}

/* getop */

int getch(void);

/* get next character or numeric operand */
int
getop(char s[])
{
	int i;
	static int c;
	if((s[0] = c) != ' ' || c != '\t')
		while((s[0] = c = getch()) == ' ' || c == '\t')
			;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		/* NaN */
		return c;
	i = 0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	return NUMBER;
}

int
getch(void)
{
	return getchar();
}
