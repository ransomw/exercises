#include <u.h> /* contains atof() */
#include <libc.h> /* contains atof() */
#include <stdio.h>
#include <ctype.h> /* contains isdigit() */
#define MAXOP	100 /* max size of operator or operand string */
#define NUMBER	'0' /* signal that a number was found */
#define MAXVAL	100 /* max stack depth */
#define BUFSIZE	100 /* getch, ungetch buffer size */
#define NUMOP	100 /* maximum number of operators pass to cli */

/* todo: this impl crudely grafts arg parsing
 * onto the orig impl.  it could be updated to
 * provide cleanear coupling.
 */

int getop(char []);
void push(double);
double pop(void);

void
main(int argc, char *argv[])
{
	void parseargs(int, char **);

	int type;
	double op2;
	char s[MAXOP];

	parseargs(argc, argv);

	while((type = getop(s)) != '\0') {
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
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

char opsarr[NUMOP][MAXOP]; /* allocate storage space */

void
parseargs(int argc, char *argv[])
{
	int i;
	for(i = 0; --argc > 0; i++)
		strcpy(opsarr[i], *++argv);
	opsarr[i][0] = '\n';
	opsarr[i+1][0] = '\0';
}


/* get next character or numeric operand */
int
getop(char *s)
{
	static int opidx;
	int i, c;
	char *op;
	
	op = opsarr[opidx++];

	while((s[0] = c = *op++) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		/* NaN */
		return c;
	i = 0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = *op++))
			;
	if(c == '.')
		while(isdigit(s[++i] = *op++))
			;
	s[i] = '\0';
	return NUMBER;
}

