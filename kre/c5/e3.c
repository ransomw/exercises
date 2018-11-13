#include <u.h>
#include <libc.h>
#include <stdio.h>
#define ALLOCSIZE	10000 /* size of available addr space */

char *alloc(int n);
void afree(char *p);

void mystrcat(char *s, char *t);
char *sstrcat(char *s, char *t);

void
main(void)
{
	char s[100] = "asdf";
	char *t, *u, *v;
	mystrcat(s, "qwer");
	printf("%s\n", s);

	t = sstrcat("zxcv", s);
	u = sstrcat("http", "qwer");
	printf("%s %s\n", t, u);

	afree(u);
	v = sstrcat("zxcv", "vcxz");
	/* u's value is an artifact of alloc impl details */
	printf("%s %s %s\n", t, u, v);

	exits(0);
}

/* verbatim functionality from c2/inc_dec.c with pointers */
void
mystrcat(char *s, char *t)
{
	while(*s)
		s++;
	while(*s++ = *t++)
		;
}

/* standard-library-like version
 * leaves strings pointed to by params unchanged
 * and uses alloc and free to create a new string
 */
char *
sstrcat(char *s, char *t)
{
	int mystrlen(char *);

	char *u, *v;
	u = v = alloc(mystrlen(s) + mystrlen(t) + 1);
	while(*u++ = *s++)
		;
	u--;
	while(*u++ = *t++)
		printf("*\t%c\n", u[-1]);
	*u = '\0';
	return v;
}

int
mystrlen(char *s)
{
	char *p = s;

	while(*p != '\0')
		p++;
	return p - s;
}

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

void
afree(char *p)
{
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
