#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h> /* isspace, isdigit, ... */
#define BUFSIZE	100 /* getch, ungetch buffer size */
#define SIZE 10 /* max number of floats to read from stdin */

void getfloats(double[], int);

void
main(void)
{
	double arr[SIZE];
	int i;

	getfloats(arr, SIZE);
	for(i = 0; i < SIZE; i++)
		printf("%g ", arr[i]);
	printf("\n");

	exits(0);
}


/* getints: wrap `getint` to fill an array with integer values */
void
getfloats(double arr[], int len)
{
	int n, getfloat(double *);

	for(n = 0; n < len && getfloat(&arr[n]) != EOF; n++)
		;
}

int getch(void);
void ungetch(int c);



int
getfloat(double *pn)
{
	int c, sign;

	while(isspace(c = getch()))
		;
	if(!isdigit(c) && c != EOF &&
		c != '+' && c != '-' &&
		c != '.') {
		/* NaN */
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	// todo: cleanup messy flow, handle exponents
	if(c != '.') {
		if(c == '+' || c == '-')
			c = getch();
		for(*pn = 0.0; isdigit(c); c = getch())
			*pn = 10 * *pn + (c - '0');
	} else
		*pn = 0.0;
	if(c == '.') {
		double power;
		c = getch();
		for(power = 1.0; isdigit(c); c = getch()) {
			*pn = 10 * *pn + (c - '0');
			power *= 10;
		}
		*pn /= power;
	}
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
