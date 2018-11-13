#include <u.h>
#include <libc.h>
#include <stdio.h>
#define HASHSIZE	1
#define MAXLINE	100

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

int
getline(char *s, int lim)
{
	int c;
	char *start = s;

	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		*s++ = c;
	*s = '\0';
	return s - start;
}

int
parseline(char *line, char *name, char *defn)
{
	static const char sep = '=';
	char *sepp;

	if(line[0] == '!') {
		strcpy(name, line + 1);
		*defn = '\0';
		return 1;
	}
	if((sepp = strchr(line, sep)) == 0) {
		strcpy(name, line);
		*defn = '\0';
	} else {
		/* todo: strecpy is probably the fn to use ... */
		strncpy(name, line, sepp - line);
		strcpy(defn, sepp + 1);
	}
	return 0;
}

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *s);

void
main(void)
{
	char line[MAXLINE];
	char name[MAXLINE], defn[MAXLINE];
	struct nlist *np;

	while(getline(line, MAXLINE) != 0) {
		if(parseline(line, name, defn))
			undef(name);
		else if(defn[0] == '\0')
			if((np = lookup(name)) == nil)
				print("%s undefined\n", name);
			else
				print("%s\n", np->defn);
		else
			install(name, defn);
	}

	exits(nil);
}

/* todo: get into (fancier) hashing functions */

unsigned
hash(char *s)
{
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

static struct nlist *hashtab[HASHSIZE];

struct nlist *
lookup(char *s)
{
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != nil; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return nil;
}

void
nlfree(struct nlist *np)
{
	free((void *) np->name);
	free((void *) np->defn);
	free((void *) np);
}

void
undef(char *s)
{
	struct nlist **tabptr, *tabent, *np, *pnp;

	tabptr = hashtab + hash(s);
	tabent = *tabptr;
	if(tabent == nil)
		return;
	/* todo: linked-list C idiom that /doesn't/
	 *	involve special handling of the root node?
	 */
	if(strcmp(s, tabent->name) == 0) {
		*tabptr = tabent->next;
		nlfree(tabent);
		return;
	}
	for(pnp = tabent, np = tabent->next;
			np != nil;
			pnp = np, np = np->next)
		if(strcmp(s, np->name) == 0) {
			pnp->next = np->next;
			nlfree(np);
			return;
		}
}

char *
strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if(p != nil)
		strcpy(p, s);
	return p;
}

struct nlist *
install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if((np = lookup(name)) == nil) {
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == nil || (np->name = strdup(name)) == nil)
			return nil;
		hashval = hash(name);
		/* cons onto front of list */
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if((np->defn = strdup(defn)) == nil)
		return nil;
	return np;
}
