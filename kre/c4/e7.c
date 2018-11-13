#include <u.h>
#include <libc.h>
#include <stdio.h>
#define BUFSIZE	100 /* getch, ungetch buffer size */

int getch(void);
void ungetch(int);
void ungets(char s[]);

void
main(void)
{
	int c;

	ungetch('x');
	ungetch('y');
	ungets("asdf");
	ungetch('z');

	while((c = getch()) != EOF)
		printf("%c", c);
	printf("\n");
}

/* external variables for getch and ungetch */

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

void
ungets(char s[])
{
	int i;
	for(i = strlen(s); i >= 0; i--)
		ungetch(s[i]);
}
