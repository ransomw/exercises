#include <u.h> /* contains atof() */
#include <libc.h> /* contains atof() */
#include <stdio.h>
#include <ctype.h> /* contains isdigit() */
#define MAXOP	100 /* max size of operator or operand string */
#define NUMBER	'0' /* signal that a number was found */
#define FN	'1' /* signal that a function was found */
#define SVAR	'2' /* signal: set variable */
#define DVAR	'3' /* signal: deref variable */
#define MAXVAL	100 /* max stack depth */
#define BUFSIZE	100 /* getch, ungetch buffer size */
#define NCVARS	26 /* characters a-z used as variables */

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

void stack_print(int);
void stack_duplicate(int n);
void stack_swap_top_two(void);
void stack_clear(void);

double eval_fn(char []);

void set_var(char name[], double val);
double deref_var(char name[]);

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
		/* arithemetic operators */
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
		// todo: could have cleaner handling than casting..
		//   .. e.g. errors on op2 not an int
		//    or handing fractional parts of the other op
		case '%':
			op2 = pop();
			if(op2 != 0.0)
				push((int) pop() % (int) op2);
			else
				exits("zero modulus");
			break;
		/* variables */
		case SVAR:
			set_var(s, pop());
			break;
		case DVAR:
			op2 = deref_var(s);
			push(op2);
			break;
		/* math functions */
		case FN:
			push(eval_fn(s));
			break;
		/* stack commands */
		case 'p':
			op2 = pop(); /* num elements to print */
			// todo: errors on op2 not an int
			stack_print(op2);
			break;
		case 'd':
			op2 = pop(); /* num elements to duplicate */
			// todo: errors on op2 not an int
			stack_duplicate(op2);
			break;
		case 's':
			stack_swap_top_two();
			break;
		case 'c':
			stack_clear();
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

/* external variables for calculator variables */
// todo: support variable names other that 'a'-'z'
//    (after chapters on pointers, structs, etc.)

double vars[NCVARS];

void
init_vars(void) {
	int i;
	for(i = 0; i < NCVARS; i++)
		vars[i] = NaN();
}

int
_var_idx(char name[])
{
	int n;
	if(strlen(name) != 1)
		exits("invalid varname (len)");
	n = name[0];
	if(n >= 'a' && n <= 'z')
		return n - 'a';
	exits("invalid varname");
	return -1;
}

void
set_var(char name[], double val)
{
	if(isNaN(val))
		exits("can't set NaN to var");
	vars[_var_idx(name)] = val;
}

double
deref_var(char name[])
{
	double val = vars[_var_idx(name)];
	if(isNaN(val))
		exits("can't deref unset var");
	return val;
}

/* eval_fn: pop appropriate stack values and apply libc.h fn */ 
double
eval_fn(char fn[])
{
	double op2;
	if(strcmp(fn, "hypot") == 0) {
		return hypot(pop(), pop());
	} else if(strcmp(fn, "pow") == 0) {
		op2 = pop();
		return pow(pop(), op2);
	} else if(strcmp(fn, "sin") == 0) {
		return sin(pop());
	}
	exits("unknown function");
	return NaN();
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

void
stack_print(int n)
{
	int i, start_idx;
	if(n < 0 || n > sp)
		start_idx = 0;
	else
		start_idx = sp - n;
	printf("stack %d> ", start_idx);
	for(i = start_idx; i < sp; i++)
		printf("%.3g ", val[i]);
	printf("<\n");
}

void
stack_duplicate(int n)
{
	int i, start_idx, sp_start = sp;
	if(n < 0 || n > sp)
		start_idx = 0;
	else
		start_idx = sp - n;
	for(i = start_idx; i < sp_start; i++)
		push(val[i]);
}

void
stack_swap_top_two(void)
{
	double top = val[sp-1], next = val[sp-2];
	val[sp-1] = next;
	val[sp-2] = top;
}

void
stack_clear(void)
{
	sp = 0;
}

/* getop */

int getch(void);
void ungetch(int);

/* get next character or numeric operand */
int
getop(char s[])
{
	int i, c, optok;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.' && c != '-' &&
		c != 'F' && c != '=' && c != '$')
		/* not a positive number or function */
		return c;
	i = 0;
	if(c == 'F' || c == '=' || c == '$') {
		optok = c;
		/* get function or variable name */
		while((s[i++] = c = getch()) != ' ' && c != '\t' &&
			c != '\n' && c != EOF)
			;
		if(c != EOF)
			ungetch(c);
		s[i-1] = '\0';
		switch(optok) {
		case 'F':
			return FN;
		case '=':
			return SVAR;
		case '$':
			return DVAR;
		default:
			exits("unrecognized name-op token");
			return -1;
		}
	}
	if(c == '-' &&
		!isdigit(s[++i] = c = getch()) &&
		c != '.') {
		/* not a negative number */
		ungetch(c);
		return '-';
	}
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

/* external variables for getch and ungetch */

char buf[BUFSIZE];
int bufp = 0;

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
