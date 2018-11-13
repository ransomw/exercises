#include <u.h>
#include <libc.h>
#include <stdio.h>

int strendnoh(char *, char *);
int strendhlp(char *, char *);

void
main(void)
{



	printf("ends with %d %d\n",
		strendnoh("asdf", "df"),
		strendhlp("asdf", "df"));
	printf("ends with %d %d\n",
		strendnoh("asdf", ""),
		strendhlp("asdf", ""));
	printf("ends with %d %d\n",
		strendnoh("", ""),
		strendhlp("", ""));

	printf("doesn't end with %d %d\n",
		strendnoh("asdf", "qasdf"),
		strendhlp("asdf", "qasdf"));
	printf("doesn't end with %d %d\n",
		strendnoh("asdf", "asdq"),
		strendhlp("asdf", "asdq"));
	printf("doesn't end with %d %d\n",
		strendnoh("", "q"),
		strendhlp("", "q"));
	printf("doesn't end with %d %d\n",
		strendnoh("a", "b"),
		strendhlp("a", "b"));
	printf("doesn't end with %d %d\n",
		strendnoh("xa", "xb"),
		strendhlp("xa", "xb"));
	printf("doesn't end with %d %d\n",
		strendnoh("asdf", "asdq"),
		strendhlp("asdf", "asdq"));


	exits(0);
}




/* strend: return 1 if t occurs at the end of s,
 *	0 otherwise
 * no helpers version
 */
int
strendnoh(char *s, char *t)
{
	char *tb = t;
	while(*s != '\0')
		s++;
	while(*t != '\0')
		t++;
	for(; tb <= t; t--, s--)
		if(*t != *s)
			return 0;
	return 1;
}

int
mystrlen(char *s)
{
	char *p = s;

	while(*p != '\0')
		p++;
	return p - s;
}


/* strend: helped version */

int
strendhlp(char *s, char *t)
{
	int ldiff = mystrlen(s) - mystrlen(t);
	if(ldiff < 0)
		return 0;
	for(s += ldiff; *s == *t && *s != '\0' ; s++, t++)
		;
	if(*s == '\0')
		if(*t == '\0')
			return 1;
		else
			exits("impl err: pointer arithmetic");
	return 0;
}
