#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define MAXWORD	100
#define MAXLINE	1000
#define BUFSIZE	100 /* getch, ungetch buffer size */

struct nnode {
	int lineno;
	struct nnode *next;
};

struct tnode {
	char *word;
	struct nnode *nnodes;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int, int *);

/* todo: remove "noise" words */

void
main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	int lineno;

	root = NULL;
	while(getword(word, MAXWORD, &lineno) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word, lineno);
	treeprint(root);
	exits(nil);
}

struct tnode *talloc(void);
struct nnode *nalloc(void);
char *strdup(char *);

struct tnode *
addtree(struct tnode *p, char *w, int lineno)
{
	int cond;
	struct nnode *nn;
	if(p == NULL) {
		p = talloc(); /* todo: error handling */
		p->word = strdup(w); /* todo: error handling */
		p->nnodes = nalloc();
		p->nnodes->lineno = lineno;
		p->nnodes->next = NULL;
		p->left = p->right = NULL;
	} else if((cond = strcmp(w, p->word)) == 0) {
		nn = p->nnodes;
		while(nn->next != NULL && nn->lineno != lineno)
			nn = nn->next;
		if(nn->lineno != lineno) {
			assert(nn->next == NULL);
			nn->next = nalloc();
			nn->next->lineno = lineno;
			nn->next->next = NULL;
		}
	} else if(cond < 0)
		p->left = addtree(p->left, w, lineno);
	else
		p->right = addtree(p->right, w, lineno);
	return p;
}

int
numtreenodes(struct tnode *p)
{
	if(p == NULL)
		return 0;
	return 1 + numtreenodes(p->left) + numtreenodes(p->right);
}

void
linenosprint(struct nnode *nn)
{
	if(nn == NULL) {
		return;
	}

	printf("%d ", nn->lineno);
	linenosprint(nn->next);
}

void
treeprint(struct tnode *p)
{
	if(p == NULL)
		return;

	treeprint(p->left);
	printf("%s: ", p->word);
	linenosprint(p->nnodes);
	printf("\n");
	treeprint(p->right);
}


struct tnode *
talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct nnode *
nalloc(void)
{
	return (struct nnode *) malloc(sizeof(struct nnode));
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

/* getword: no C-specific handling */

int getch(void);
void ungetch(int c);
int currlineno = 0;

int
getword(char *word, int lim, int *linenop)
{
	/* functions can be declared alongside variables */
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
	*linenop = currlineno;
	if(c != EOF)
		*w++ = c;
	if(!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for( ; --lim > 0; w++)
		if(!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

char buf[BUFSIZE];
int bufp = 0;

void
ungetch(int c)
{
	if(bufp >= BUFSIZE)
		exits("ungetch buffer full");
	else
		buf[bufp++] = c;
}

char currline[MAXLINE];
int currlinep = 0;

int
getlinech(void)
{
	int getline(char *s, int lim);

	if(currline[currlinep] != '\0')
		return currline[currlinep++];
	if(getline(currline, MAXLINE) == 0)
		return EOF;
	currlineno++;
	currlinep = 0;
	return getlinech();
}

int
getch(void)
{
	return bufp > 0 ?
		buf[--bufp] :
		getlinech();
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
