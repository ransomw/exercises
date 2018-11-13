#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h> /* isspace, isdigit, ... */
#define BUFSIZE	100 /* getch, ungetch buffer size */
#define SIZE 10 /* max number of integers to read from stdin */

void getints(int[], int);

void
main(void)
{
	int arr[SIZE], i;

	getints(arr, SIZE);
	for(i = 0; i < SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");

	exits(0);
}


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
	if(c == '+' || c == '-') {
		/* todo: this is a rather literal interpretation
		 *  of what i read the exercise to mean.
		 * need to revisit to see if the wording is clearer
		 * on re-reading and then either change the behavior
		 * if i'm misunderstanding or clean up the impl
		 * even if i'm reading correctly.
		 */
		int signch = c;
		if(!isdigit(c = getch())) {
			ungetch(c);
			return signch;
		}
	}
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
