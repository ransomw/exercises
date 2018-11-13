#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINES	5000
#define MAXLEN	1000
#define ALLOCSIZE MAXLINES * MAXLEN

/** cf. fnptr_sort.c comments */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void mwritelines(char *lineptr[], int nlines);

void mqsort(char *lineptr[], int left, int right,
		int (*comp)(void *, void *));
int numcmp(char *, char*);

void reverse(void *[], int);
int fcstrcmp(char *s, char *t);

void
main(int argc, char *argv[])
{
	int c;
	int nlines;
	int numeric = 0, reversed = 0, foldcase = 0;
	int (*cmpfnptr)(void *, void*);

	while(--argc > 0 && (*++argv)[0] == '-') {
		while(c = *++argv[0])
			switch(c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reversed = 1;
				break;
			case 'f':
				foldcase = 1;
				break;
			default:
				printf("illegal option %c\n", c);
				exits("illegal option");
				argc = 0;
				break;
			}
	}
	
	if(numeric)
		cmpfnptr = (int (*)(void *, void *)) numcmp;
	else if(foldcase)
		cmpfnptr = (int (*)(void *, void *)) fcstrcmp;
	else
		cmpfnptr = (int (*)(void *, void *)) strcmp;

	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		mqsort((void **) lineptr, 0, nlines - 1,
			cmpfnptr);
		if(reversed)
			reverse(lineptr, nlines);
		mwritelines(lineptr, nlines);
	} else {
		exits("input too big to sort");
	}

	exits(0);
}

void
lower(char *s)
{
	int i, c;

	for(i = 0; (c = s[i]) != '\0'; i++)
		if(c >= 'A' && c <= 'Z')
			s[i] = 'a' + (c - 'A');
}

int
fcstrcmp(char *s, char *t)
{
	char sc[MAXLEN], tc[MAXLEN];

	strcpy(sc, s);
	strcpy(tc, t);

	lower(sc);
	lower(tc);
	return strcmp(sc, tc);
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
reverse(void *v[], int nptr)
{
	int i;

	for(i = 0; i < --nptr; i++)
		swap(v, i, nptr);
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
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
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

