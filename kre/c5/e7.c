#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINES	5000 /* max num lines to be sorted */
#define MAXLEN	1000 /* max length of any given input line */
#define ALLOCSIZE MAXLINES * MAXLEN

/**
 * read lines from stdin 'til EOF and print lexicographically
 * sorted list of lines
 */

int readlines(char *lineptr[], int nlines);
void mwritelines(char *lineptr[], int nlines);

void mqsort(char *lineptr[], int left, int right);

void
main(void)
{
	char linearr[MAXLINES][MAXLEN];
	char *lineptr[MAXLINES];
	int nlines; /* number of input lines read */
	int i;
	
	for(i = 0; i < MAXLINES; i++)
		lineptr[i] = linearr[i];

	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		mqsort(lineptr, 0, nlines - 1);
		mwritelines(lineptr, nlines);
	} else {
		exits("input too big to sort");
	}

	exits(0);
}

void
swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* similar to c4/recursion.c */
void
mqsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++)
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	mqsort(v, left, last - 1);
	mqsort(v, last + 1, right);
}

int getline(char *, int);
char *alloc(int);

/**
 * in this exercise, lineptr already has sufficient
 * (MAXLEN) storage space allocated at each pointer
 */
int
readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char line[MAXLEN];

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
		if(nlines >= maxlines)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(lineptr[nlines++], line);
		}


	return nlines;
}

/* for comparison with the following function */
void
writelinesarr(char *lineptr[], int nlines)
{
	int i;

	for(i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void
mwritelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
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
