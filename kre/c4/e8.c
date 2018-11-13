#include <u.h>
#include <libc.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

void
main(void)
{
	char s[] = "asdf";
	int slen = strlen(s);
	int i, k, c;

	/* print alternating from stdin and s */
	for(i = 0; (c=getch()) != EOF; i++) {
		if(i % 2 == 0 && (k = i / 2) <= slen)
			ungetch(s[k]);
		printf("%c", c);
	}

	printf("\n");
	exits(0);
}

/* external variables for getch and ungetch */

char buf = '\0';

int
getch(void)
{
	int c;
	if(buf == '\0')
		return getchar();
	c = buf;
	buf = '\0';
	return c;
}

void
ungetch(int c)
{
	if(buf == '\0')
		buf = c;
	else
		exits("ungetch one-char buffer full");
}

