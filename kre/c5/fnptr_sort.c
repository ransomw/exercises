#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINES	5000 /* max num lines to be sorted */
#define MAXLEN	1000 /* max length of any given input line */
#define ALLOCSIZE MAXLINES * MAXLEN

/**
 * read lines from stdin 'til EOF list of lines,
 * sorted according to command-line param.
 *
 * this is a modified version of sort.c to demonstrate
 * pointers to functions:  functions themselves cannot
 * be variables, so pointers are used to treat them as variables.
 */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void mwritelines(char *lineptr[], int nlines);

/* this declares a function pointer as a parameter. specifically,
 * comp is a pointer to a function that takes two void *
 * args and returns an int.
 *
 * the full grammar is left to an appendix.
 * for now, contrast
 * `int *comp()` - a fn returning a pointer to an int
 * and
 * `int (*comp)()` - a pointer to a fn returning an int
 *
 * this is the first use of void pointers in the text.
 * since pointers contain memory addresses and all memory
 * addresses are the same size, any pointer type can be
 * cast to and from void pointers.
 *
 * however, pointer arithmetic cannot be performed on void
 * pointers since they contain no information about how many
 * memory addresses correspond to a value.
 */ 
void mqsort(char *lineptr[], int left, int right,
		int (*comp)(void *, void *));
int numcmp(char *, char*);

void
main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0;

	if(argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;

	/* just as it's not necessary to use `&` with array names,
	 * the compiler similarly knows that function names
	 * in expressions refer to memory addresses.
	 */
	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		mqsort((void **) lineptr, 0, nlines - 1,
			(int (*)(void *, void *))(
				numeric ? numcmp : strcmp));
		mwritelines(lineptr, nlines);
	} else {
		exits("input too big to sort");
	}

	exits(0);
}

void
swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void
mqsort(char *v[], int left, int right,
	int (*comp)(void *, void*))
{
	int i, last;
	void swap(void *v[], int, int);

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++)
		/* as usual, derefing a ptr returns its value.
		 * (*comp) a function returning an `int`
		 * with params (void *, void*)
		 */
		if((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	mqsort(v, left, last - 1, comp);
	mqsort(v, last + 1, right, comp);
}

void
mwritelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int
numcmp(char *s, char *t)
{
	double u, v;


	u = atof(s);
	v = atof(t);
	if(u < v)
		return -1;
	if(u > v)
		return 1;
	return 0;
}

int getline(char *, int);
char *alloc(int);

int
readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/** modified from c4/e1.c to use pointers */
int
getline(char *s, int lim)
{
	int c = EOF;
	char *start = s;

	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = c;
	*s = '\0';
	return s - start;
}

/** from alloc_and_free.c */

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *
alloc(int n)
{
	/* note that, in addition to the - operator,
	 * comparison operators ==, !=, <, >, <=, >=
	 * also apply to pointers, because the address
	 * space is linerarly ordered.
	 */
	if(allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		/**** 0 is never a valid memory address ****/
		return allocp - n;
	} else
		/* conversely, 0 is the only valid integer literal
		 * that can be assigned to a pointer variable.
		 */
		return 0;
}

