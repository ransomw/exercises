#include <u.h>
#include <libc.h>
#include <stdio.h>

/* silly block structure sandbox.
 * in C, "blocks" are {compound; statements;}
 */

void printseq(int n);

void
main(void)
{
	printseq(3);
	printseq(-3);
	exits(0);
}

/* external variable declarations as per usual */
double i = 3.21;
float n = 1.1;

/* print ascending sequence between n and zero */
void
printseq(int n)
{
	/* internal variable declaration as usual,
	 * except declarations in function bodies (as a particular
	 * case of compound statements) override external
	 * declarations of the same *name* (incl. type info).
	 *
	 * function parameters, too, while not strictly part of
	 * the block, follow the same general trend of overriding
	 * external names.
	 */
	int i = 123;
	printf("test: %d %d\n", i, n);
	if(n > 0) {
		/*
		 * variables can be declared at the beginning
		 * of any compound statement (i.e. several
		 * statements in {...}s).
		 *
		 * as with internal variables and function
		 * parameters, block scope variables hide
		 * outer variables.
		 */
		int i;
		for(i = 0; i <= n; i++)
			printf("%d ", i);
	} else {
		int i;
		for(i = n; i <= 0; i++)
			printf("%d ", i);
	}
	printf("\n");
}

/* in general, it's bad practice to avoid naming
 * conventions that lead to confusion as a result of
 * block scope overrides.  this example is for demonstration only.
 */
