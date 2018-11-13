#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h> /* isspace, isdigit, ... */
#define BUFSIZE	100 /* getch, ungetch buffer size */
#define SIZE 10 /* max number of integers to read from stdin */

/** run by piping a string of integers to stdin */

/* recall that C functions get parameters "by value"
 * in that, when a variable is passed to a function,
 * the function gets a copy of its value,
 * not a named reference to the variable itself.
 *
 * passing pointers to functions allows functions
 * to change the values of variables named in a scope
 * that the function doesn't have access to.
 *
 * as an aside, the text's word-choice continues to suggest
 * that object-oriented programming metaphors are a loosely
 * analogous mental model to bear in mind when working with
 * pointers.
 */

void swap(int *, int *);
void getints(int arr[], int len);

void
main(void)
{
	int a, b;
	int arr[SIZE], i;

	a = 1; b = 2;
	printf("%d %d\n", a, b);
	swap(&a, &b);
	printf("%d %d\n", a, b);

	getints(arr, SIZE);
	for(i = 0; i < SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");

	exits(0);
}

/* interchange *px and *py */
void
swap(int *px, int *py)
{
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}

/*
as a more complex example, consider the task of using a function
to parse a sequence of integers from stdin, one int per call.
in particular, the function need signal when EOF is reached.

this function will be called `getint`

since EOF is itself an integer, there must be separate data paths,
different wires signaling EOF and integer values.
a function that returns an int and doesn't receive pointer values
will not suffice.

the following function will use the return value of `getint`
to signal EOF and pass pointers to obtain values.
*/

/* getints: wrap `getint` to fill an array with integer values */
void
getints(int arr[], int len)
{
	int n, getint(int *);

	for(n = 0; n < len && getint(&arr[n]) != EOF; n++)
		;
}

int getch(void);
void ungetch(int c);

int
getint(int *pn)
{
	int c, sign;

	while(isspace(c = getch()))
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		/* NaN */
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
		c = getch();
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}

/* as in c4/rp_calc.c */

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
