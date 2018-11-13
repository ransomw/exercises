#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100 /* maximum keyword length */
#define BUFSIZE	100 /* getch, ungetch buffer size */

/* this program appears in 6.3 to demonstrate arrays of
 * structures.
 */

/* arrays of structures can be initialized with either nested
 * or flat lists.
 */

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	/* ... be sure to enter in alphabetical order. */
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

struct key keytabb[] = {
	{"auto", 0},
	{"break", 0}
};

/* the text recommends calculating the number of
 * elements in keytab with this ANSI-C standard
 * convention:  sizeof is a unary operator (like ++)
 * that returns the number of bytes allocated to
 * an object -- i.e. a variable, array, or struct.
 *
 * in particular, sizeof is a compile-time operator.
 * it can only determine the size of things defined at compile
 * time.
 */
#define NKEYS (sizeof keytab / sizeof(struct key))
/* this particular macro could just as well be
	(sizeof keytab / sizeof(keytab[0]))
*/

int binsearch(char *, struct key *, int);
int getword(char *word, int lim);

void
main(void)
{
	int n;
	char word[MAXWORD];

	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			if((n = binsearch(
				word, keytab, NKEYS)
					) >= 0)
				keytab[n].count++;
	for(n = 0;
		/* nelem() is available on Plan 9
		 * to do the job of the NKEYS macro
		 */
		n < nelem(keytab);
		n++)
		if(keytab[n].count > 0)
			printf("%4d %s\n",
				keytab[n].count,
				keytab[n].word);

	exits(nil);
}

int
binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low + high) / 2;
		if((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if(cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int
getword(char *word, int lim)
{
	/* functions can be declared alongside variables */
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while(isspace(c = getch()))
		;
	if(c != EOF)
		*w++ = c;
	if(!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for( ; --lim > 0; w++)
		if(!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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
