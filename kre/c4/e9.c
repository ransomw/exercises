#include <u.h>
#include <libc.h>
#include <stdio.h>
#define BUFSIZE	100 /* getch, ungetch buffer size */

int getch(void);
void ungetch(int);

// todo: uncertain why original getch/ungetch impl is incorrect
void
main(void)
{
	int c;

	ungetch(EOF);
	printf("%c\n", getch());

	while((c=getch()) != EOF)
		printf("%c", c);

	printf("\n");
	exits(0);
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
	if(c == EOF)
		return;
	if(bufp >= BUFSIZE)
		exits("ungetch buffer full");
	else
		buf[bufp++] = c;
}
