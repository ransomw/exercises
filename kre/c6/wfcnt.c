#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define MAXWORD	100
#define BUFSIZE	100 /* getch, ungetch buffer size */

/* 6.5 self-referential structures */

/* although a tagged structure `struct <tag>` cannot 
 * contain a member that is of type `struct <tag>`,
 * it can contain pointers to `struct <tag>` types.
 *
 * without tags, there's no way to reference a structure
 * separately from its full declaration, so self-referential
 * structures without pointers are of finite depth.
 *
 * similarly, mutually-referential structures are
 * implemented with pointers as in
	struct t { struct s *p;};
	struct s { struct t *q;};
 */
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

void
main(void)
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	exits(nil);
}

/* recursive tree functions
 * NB. these functions make no attempt to balance trees
 */

struct tnode *talloc(void);
char *strdup(char *);

/* add a word to the tree rooted at p,
 * either by creating a node or incrementing the count of a node.
 * return the updated tree rooted at p or a new node if p is NULL.
 */
struct tnode *
addtree(struct tnode *p, char *w)
{
	int cond;

	if(p == NULL) {
		p = talloc(); /* todo: error handling */
		p->word = strdup(w); /* todo: error handling */
		p->count = 1;
		p->left = p->right = NULL;
	} else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if(cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void
treeprint(struct tnode *p)
{
	if(p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* memory (aka storage) allocation functions
 * these functions wrap malloc in order to cast
 * void pointers to typed pointers.
 *
 * malloc() returns NULL when there's no available
 * memory, and both of these functions pass error-handling
 * along to callers.
 *
 * free() can be used to allow storage from a malloc call
 * to be re-used later
 */

struct tnode *
talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *
strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}

/* e1.c getword version */

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
