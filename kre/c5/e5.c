#include <u.h>
#include <libc.h>
#include <stdio.h>
#define ALLOCSIZE	10000 /* size of available addr space */

char *alloc(int n);
void afree(char *p);

char *sstrncat(char *, char *, long);
char *sstrncpy(char *, char *, long);
int sstrncmp(char *, char *, long);


void
main(void)
{
	char s[100];
	char t[] = "asdf";

	printf("%s ", sstrncat(strcpy(s, "qwer"), t, 3));
	printf("%s ", sstrncat(strcpy(s, "qwer"), t, 4));
	printf("%s ", sstrncat(strcpy(s, "qwer"), t, 5));
	printf("\n");

	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 2));
	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 3));
	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 4));
	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 5));
	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 6));
	printf("%s ", sstrncpy(strcpy(s, "qwer"), t, 7));
	printf("\n");

	printf("equal %d %d %d %d %d %d %d\n",
		sstrncmp("asdf", "asdg", 3),
		sstrncmp("asdf", "asdg", 2),
		sstrncmp("asdf", "asdg", 0),
		sstrncmp("asdf", "asdf", 3),
		sstrncmp("asdf", "asdf", 4),
		sstrncmp("asdf", "asdf", 5),
		sstrncmp("asdf", "asdf", 6));
	printf("before %d %d %d\n",
		sstrncmp("asdf", "asdg", 4),
		sstrncmp("asdf", "asdg", 5),
		sstrncmp("abdf", "asdg", 2));


	exits(0);
}

/* append at most n characters of t to s */
char *
sstrncat(char *s, char *t, long n)
{
	char *u, *v;
	u = s;
	while(*u)
		u++;
	v = t;
	/* precedence requires parens around assignment */
	while((*u++ = *v++) && v - t < n)
		;
	*u = '\0';
	return s;
}

/* copy precisely n bytes from t to s,
 * adding null bytes if s doesn't have enough
 */
char *
sstrncpy(char *s, char *t, long n)
{
	long i;
	char *u, *v;

	u = s;
	v = t;
	while((*u++ = *v++) && v - t < n)
		;
	/* add padding
	 *
	 * the ? op handles while loop exit on first
	 * condition when v - t < n is true as well.
	 */
	for(i = n - (v - t) + (!v[-1] ? 1 : 0); i > 0; i--)
		*u++ = '\0';
	*u = '\0';
	return s;
}

/* strcmp* fns compare the lexicographic (dictionary)
 * ordering of at most the first n characters of strings s and t
 * returns:
 *	<0 if s<t
 *	0 if s==t
 *	>0 if s>t
 */
int
sstrncmp(char *s, char *t, long n)
{
	char *u = s;

	/* break when u is the nth element from s */
	for(; *u == *t && u - s + 1 < n; u++, t++)
		if(*u == '\0')
			return 0;
	/* if loop breaks on len cond, compare the last element */
	return *u - *t;
}
