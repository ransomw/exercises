#include <u.h>
#include <libc.h>
#include <stdio.h>
/* the #define directive has the general form
#define /name/ /replacement-text/
 * with line-continuations occuring the replacement text as in
 */
#define TWO	1 \
+ \
1

/* it's possible to pass parameters to macros, as in */
#define max(A, B)	((A) > (B) ? (A) : (B))
/* although a general form for this isn't mentioned
 * in the main text.
 * todo: check appendix
 *
 * notice also that it's good practice to parenthesize
 * macro parameters used with operators since, unlike
 * function calls, the textual substitution in macros
 * doesn't enforce any rules about precedence and the user
 * of a macro might not remember to work out precedence rules
 * within the expanded text.
 */


#define say() "hi"
/* there's also an #undef directive */
#undef say

/* despite differences from functions, macros are helpful.
 * they don't require the runtime overhead of function calls
 * and allow for some patterns that aren't possible with functions.
 * here's a useful debugging macro..
 * a #param form in the replacement text indicates that
 * param ought to be a quoted string, although this functionality
 * might not (???) be included in the plan9 preprocessor.
 */
#define dprint(EXPR)	#EXPR
// todo: debug quoting strings if present in plan 9
// #define dprint(expr)
// printf(" -- %g\n", EXPR)
// printf(#EXPR " -- %g\n", EXPR)

/* ## in a define concatenates two parameters, so
 * paste(z, 1)
 * is expected to expand to
 * z1
 * although this functionality also appears to be missing
 * from the plan9 preprocessor
 *
 * todo: look into the plan9 preprocessor's facilities
 * to concatentate params.
 */
// #define paste(A, B)	A ## B


void
say(char s[])
{
	printf("hello, %s\n", s);
}

void
main(void)
{
	int i;

//	double x, y, z1;

	char TWOTHINGS[] = "ab";
	/* substitution doesn't occur in quoted strings */
	printf("TWO %d\n", TWO);
	/* or within tokens, i.e. the leaf nodes in the
	 * tree that the compiler builds according to
	 * language syntax (as separate from language semantics)
	 * immediately upon reading a source file.
	 *
	 * so the preprocessor needs to be aware of the C grammar.
	 */
	printf("%s\n", TWOTHINGS);

	/* be particularly careful with macros with parameters
	 * as they perform textual substitution only,
	 * unlike functions.
	 */
	i = 2;
	/* here, the first macro appears to be just like a function
	 * while the second macro substitution reveals different
	 * behavior.
	 */
	printf("%d %d %d\n",
		max(1, 2), max(1, i++), i);

	/* because of #undef, this does not say "hi" */
	say("world");

	/* see todo above */
//	x = 2.0, y = 1.0;
//	printf("%s\n", dprint(x+y));
	/* recall that the compiler concatenates adjacent
	 * string literals
	 */
	printf("asfd" "qwer" "\n");

//	paste(z, 1) = 1.23;
//	printf("%g\n", z1);

	exits(0);
}

/* note: conditional inclusion isn't included
 * b/c the plan9 system doesn't use this facility
 */
