#include <u.h>
#include <libc.h>
#include <stdio.h>

/* string constants such as
	"asdf"
 * are arrays of characters with a '\0' appended.
 *
 * recall that arrays aren't passed as function parameters,
 * pointers are, so (char *s) and (char s[]) are equivalent.
 * en particular,
	printf("asdf")
 * is passing a pointer to the beginning of the array
 * `{'a', 's', 'd', 'f', '\0'}` to printf.
 * the `"asdf"` literal allocates space and initializes
 * the array in memory and everything else is just as in
 * ptrs_and_addrs.c
 *
 * similarly,
	char *s;
	s = "asdf";
 * allocates space in memory and assigns a pointer to the
 * beginning of the array to s.
 * and also like in ptrs_and_addrs.c,
	char s[] = "asdf";
 * is distinct from
	char *s = "asdf";
 * in that the name of an array is not an 'l-value'.
 *
 * the C lang doesn't process strings of characters as a unit.
 * all language operations on strings are done in terms
 * of pointers and arrays, while library functions can
 * provide string processing utilities.
 */

/* as a special note, observe that
	*p++ = val;
	val = *--p;
 * are standard idioms to push and pop a stack, resp
 */

void strcpyidx(char *s, char *t);
void strcpyptr(char *s, char *t);

void strcpyp(char *s, char *t);
void mystrcpy(char *s, char *t);

int strcmpidx(char *s, char *t);
int strcmpptr(char *s, char *t);

void
main(void)
{
	char *s, *t, *u;

	/* this is what pointer operations look like:
	 * there's only one copy of a string stored in memory
	 * per string constant (or 'literal').
	 */
	s = "asdf";
	t = s;
	t[0] = 'b';
	printf("%s %s\n", t, s);

	/* compare that with the following functions
	 * to produce multiple copies of the same string
	 * i.e. to place the same array in different
	 * locations in memory
	 */
	/* first, allocate some additional memory addresses */
	t = "xxxx";
	u = "xxxx";
	/* do the copy */
	strcpyidx(t, s);
	strcpyptr(u, t);
	/* change the arrays */
	t[0] = 'c';
	u[0] = 'd';
	printf("%s %s %s\n", s, t, u);

	/* again from the top, and cleaner */
	s = "wert";
	strcpyp(t, s);
	mystrcpy(u, t);
	t[0] = 'c';
	u[0] = 'd', u[3] = 'p';
	printf("%s %s %s\n", s, t, u);

	printf("\nstrcmp demos\n");
	printf("same %d %d %d %d\n",
		strcmpidx("asdf", "asdf"),
		strcmpidx("", ""),
		strcmpptr("asdf", "asdf"),
		strcmpptr("", ""));
	printf("less %d %d %d %d\n",
		strcmpidx("asd", "asdf"),
		strcmpidx("asdf", "asdg"),
		strcmpptr("asd", "asdf"),
		strcmpptr("asdf", "asdg"));
	printf("more %d %d %d %d\n",
		strcmpidx("asdf", "asd"),
		strcmpidx("asdg", "asdf"),
		strcmpptr("asdf", "asd"),
		strcmpptr("asdg", "asdf"));

	exits(0);
}

/* in this string copy function, an index variable
 * changes while the pointers to the strings remain constant
 */
void
strcpyidx(char *s, char *t)
{
	int i;

	for(i = 0; (s[i] = t[i]) != '\0';)
		i++;
}

/* this string copy function increments the pointers themselves */
void
strcpyptr(char *s, char *t)
{
	while((*s = *t) != '\0')
		s++, t++;
}

/* slight variation on the preceeding */
void
strcpyp(char *s, char *t)
{
	/* recall from pts_and_addrs.c
	 * that `*s++` is equivalent to `*(s++)`
	 * due to associativity (the parse tree,
	 * not runtime precedence).
	 *
	 * so `s++` both fetches the pointer to the current
	 * value of `s` to be dereferenced as well as incrementing
	 * the pointer.  in particular, the inc doesn't
	 * occur until after the value to dereference is fetched.
	 */
	while((*s++ = *t++) != '\0')
		;
}

/* further refinement */
void
mystrcpy(char *s, char *t)
{
	/* this version makes use of the fact that
	 * the null character '\0' is a mnemonic for 0
	 * conditional expressions are semantically
	 * false if 0, true otherwise.
	 */
	while(*s++ = *t++)
		;
}

/* strcmp* fns compare the lexicographic (dictionary)
 * ordering of strings
 * returns:
 *	<0 if s<t
 *	0 if s==t
 *	>0 if s>t
 */

int
strcmpidx(char *s, char *t)
{
	int i;

	for(i = 0; s[i] == t[i]; i++)
		if(s[i] == '\0')
			/* t[i] == 0 as well */
			return 0;
	return s[i] - t[i];
}

int
strcmpptr(char *s, char *t)
{
	/* here, it's necessary to separate inc and deref */
	for(; *s == *t; s++, t++)
		if(*s == '\0')
			return 0;
	return *s - *t;
}
