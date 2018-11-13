#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100 /* maximum keyword length */
#define BUFSIZE	100 /* getch, ungetch buffer size */

int getword(char *word, int lim);

void
main(void)
{
	char word[MAXWORD];

	while(getword(word, MAXWORD) != EOF)
		/* as in cntkw.c */
		if(isalpha(word[0]))
			printf("%s\n", word);
		/* also print those not visible in cntkw.c
		 * with preceeding whitespace (since words
		 * don't contain whitespace).
		 */
		else
			printf(" %s\n", word);

	exits(nil);
}

int getch(void);
void ungetch(int);

int
getword(char *word, int lim)
{
	/* functions can be declared alongside variables */
	int c, cc;
	char *w = word;

	while(isspace(c = getch()))
		;
	/* perhaps comments */
	if(c == '/')
		if((cc = getch()) == '/') {
			while(getch() != '\n')
				;
			return getword(word, lim);
		} else if(cc == '*') {
			while(!(c == '*' && cc == '/')) {
				c = cc;
				cc = getch();
			}
			return getword(word, lim);
		} else
			ungetch(cc);
	if(c != EOF)
		*w++ = c;
	/* quoted strings */
	if(c == '"') {
		for(; --lim > 0; w++)
			if((*w = getch()) == '"' &&
				w[-1] != '\\') {
				w++;
				break;
			}
		*w = '\0';
		return word[0];
	}
	if(!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for( ; --lim > 0; w++)
		if(!isalnum(*w = getch()) &&
			*w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

/* as in c4/rp_calc.c */

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
