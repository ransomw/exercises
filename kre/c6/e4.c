#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define MAXWORD	100
#define BUFSIZE	100 /* getch, ungetch buffer size */

/* this exercise is a modified version of wfcnt.c
 * copied from the text
 */

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct lnode {
	char *word;
	int count;
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

/* todo: get into tree balancing */

struct tnode *talloc(void);
char *strdup(char *);

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

int
numtreenodes(struct tnode *p)
{
	if(p == NULL)
		return 0;
	return 1 + numtreenodes(p->left) + numtreenodes(p->right);
}

void
swap(struct lnode l[], int i, int j)
{
	struct lnode temp;

	temp = l[i];
	l[i] = l[j];
	l[j] = temp;
}

void
mqsort(struct lnode l[], int left, int right)
{
	int i, last;

	if(left >= right)
		return;
	swap(l, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++)
		if(l[i].count > l[left].count)
			swap(l, ++last, i);
	swap(l, left, last);
	mqsort(l, left, last - 1);
	mqsort(l, last + 1, right);
}

void
flattree(struct tnode *p, struct lnode *l)
{
	if(p == NULL)
		return;
	l[0].word = strdup(p->word);
	l[0].count = p->count;
	flattree(p->left, l + 1);
	flattree(p->right, l + 1 + numtreenodes(p->left));
}

void
treeprint(struct tnode *p)
{
	int i, n = numtreenodes(p);
	struct lnode *l = malloc(sizeof(struct lnode) * n);

	flattree(p, l);
	mqsort(l, 0, n);
	for(i = 0; i < n; i++)
		printf("%4d %s\n", l[i].count, l[i].word);
	free(l);
}

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

/* getword: no C-specific handling */

int getch(void);
void ungetch(int c);

int
getword(char *word, int lim)
{
	/* functions can be declared alongside variables */
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
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
