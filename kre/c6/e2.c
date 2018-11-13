#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define MAXWORD	100
#define BUFSIZE	100 /* getch, ungetch buffer size */




void
main(void)
{

	exits(nil);
}

int getword(char *word, int lim);

/* todo: this exercise. mor practice building state machines first */

/* from A.8, variable declarations have the grammar

declaration:
	declaration-specifiers init-declarator-list_opt

declaration-specifiers:
	storage-class-specifier declaration-specifiers_opt
	type-specifier declaration-specifiers_opt
	type-qualifier declaration-specifiers_opt

init-declarator-list:
	init-declarator
	init-declarator , init-declarator-list

init-declarator:
	declarator
	declarator = initializer

----

declarator:
	pointer_opt direct-declarator

direct-declarator:
	identifier
	(declarator)
	direct-declarator[constant-expression_opt]
	direct-declarator(parameter-type-list)
	direct-declarator(identifier-list_opt)

pointer:
	* type-qualifier-list_opt
	* type-qualifier-list_opt pointer

type-qualifier-list:
	type-qualifier
	type-qualifier-list type-qualifier
*/

static const char *storage_class_specifiers[] = {
	"auto",
	"register",
	"static",
	"extern",
	"typedef"
};

static const char *type_specifiers[] = {
	"void",
	"char",
	"short",
	"int",
	"long",
	"float",
	"double",
	"signed",
	"unsigned"
	/* struct or union tag (match brackets to get to var name) */
	/* enum tag (match brackets) */
	/* typedef name */
};

static const char *type_qualifiers[] = {
	"const",
	"volatile"
};

int
getvarname(char *vn, int lim)
{

	return -1;
}

int getch(void);
void ungetch(int c);

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
	/* discard preprocessor statements */
	if(c == '#') {
		while(getch() != '\n')
			;
		return getword(word, lim);
	}
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
