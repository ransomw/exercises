#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100 /* maximum keyword length */
#define BUFSIZE	100 /* getch, ungetch buffer size */

/* this program appears in 6.4 to demonstrate arrays of
 * structures and pointers to structures.
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

struct key *binsearch(char *, struct key *, int);
int getword(char *word, int lim);

void
main(void)
{
	char word[MAXWORD];
	struct key *p;

	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			if((p = binsearch(
				word, keytab, NKEYS)
					) != NULL)
				p->count++;
	for(p = keytab;
		p < keytab + NKEYS;
		p++)
		if(p->count > 0)
			printf("%4d %s\n", p->count, p->word);

	exits(nil);
}

struct key *
binsearch(char *word, struct key tab[], int n)
{
	int cond;
	struct key *low = &tab[0];
	/* although tab[n-1] is the last element of the array,
	 * C guarantees that &arr[nelem(arr)] is a valid pointer,
	 * although the resulting pointer can't be dereferenced.
	 *
	 * pointers to other array indices (e.g. &arr[-1])
	 * are not legal.
	 *
	 * the language does *not* gaurantee 
	 * sizeof(key) == sizeof(char *) + sizeof(int)
	 * i.e. the bytes allocated to a structure is
	 *	not necessarily the number of bytes allocated
	 *	to each of its members
	 */
	struct key *high = &tab[n];
	struct key *mid;

	while(low <= high) {
		/* remember:  addition of pointers is nonsense.
		 * pointer arithmetic includes PTR + INT -> PTR
		 * and PTR - PTR -> INT
		 */
		mid = low /* ptr */ + 
			(high - low) /* int */ 
				/ 2;
		if((cond = strcmp(word, mid->word)) < 0)
			/* todo: revisit this difference
			 *	with cntkw_v1.c
			 */
			high = mid;
		else if(cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
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
