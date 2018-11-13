#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define MAXLINES	5000 /* max num lines to be sorted */
#define MAXLEN	1000 /* max length of any given input line */
#define ALLOCSIZE MAXLINES * MAXLEN

/* much from sort.c */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlineptr);
void mwritelines(char *lineptr[], int nlines);

void
main(int argc, char *argv[])
{
	int nlines;
	int ntail = -1;

	while(--argc > 0 && (*++argv)[0] == '-') {
		if(isdigit((*argv)[1])) {
			if(ntail != -1)
				exits("duplicate param");
			if((ntail = atoi(*argv + 1)) < 1)
				exits("invalid number of lines");
			continue;
		}
	}

	if(ntail > MAXLINES)
		/* malloc not yet discussed */
		exits("too many lines to tail");
	if(ntail < 1)
		exits("no lines to tail");

	nlines = readlines(lineptr, ntail);

	if(nlines > 0)
		mwritelines(lineptr, nlines);
	else if(nlines == 0)
		exits("no input");
	else
		exits("long line");

	exits(0);
}

void
mwritelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int getline(char *, int);
char *alloc(int);
void lrot(char *lineptr[], int nlines, int n);

/* read lines from stdin into lineptr,
 * discarding earlier lines if there aren't enough pointers.
 * return number of lines read _and kept_ in lineptr.
 */
int
readlines(char *lineptr[], int nlineptr)
{
	int len, lineidx, haswrapped, nlines;
	char *p, line[MAXLEN];

	lineidx = 0;
	haswrapped = 0;

	while((len = getline(line, MAXLEN)) > 0) {
		if(lineidx == nlineptr) {
			lineidx = 0;
			haswrapped = 1;
		}
		if((p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[lineidx++] = p;
		}
	}

	if(haswrapped) {
		nlines = nlineptr;
		lrot(lineptr, nlines, lineidx);
	} else
		nlines = lineidx;
	return nlines;
}

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

void
swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* left rotate by one */
// todo: this is a bit of a mess
void
lrotone(char *lineptr[], int nlines)
{
	int i;
	char *head;

	head = lineptr[0];
	for(i = 0; i < nlines - 1; i++)
		swap(lineptr, i, i + 1);
	lineptr[nlines - 1] = head;
}

void
lrot(char *lineptr[], int nlines, int n)
{
	int i;

	for(i = 0; i < n; i++)
		lrotone(lineptr, nlines);
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *
alloc(int n)
{
	if(allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}
