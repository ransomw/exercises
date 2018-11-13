#include <u.h>
#include <libc.h>
#include <stdio.h>
#define HASHSIZE	101
#define MAXLINE	100

/* everything below main() and this struct are the "innards"
 * of 6.6.  the rest is a read loop to implement an in-memory
 * key-value store.
 *
 * input lines are of the form
	key=val
 * or
	key
 */

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

void
parseline(char *line, char *name, char *defn)
{
	static const char sep = '=';
	char *sepp;

	if((sepp = strchr(line, sep)) == 0) {
		strcpy(name, line);
		*defn = '\0';
	} else {
		/* todo: strecpy is probably the fn to use ... */
		strncpy(name, line, sepp - line);
		strcpy(defn, sepp + 1);
	}
}

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

void
main(void)
{
	char line[MAXLINE];
	char name[MAXLINE], defn[MAXLINE];
	struct nlist *np;

	while(getline(line, MAXLINE) != 0) {
		parseline(line, name, defn);
		if(defn[0] == '\0')
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
