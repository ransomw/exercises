#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXVAL	100 /* maximum number of elements on the stack */

/* the `extern` token *declares* variables.
 * this is different from *defining* variables.
 *
 * external variables and functions must be declared or defined
 * before they are used --- i.e. their scope starts at
 * their definition or declaration and continues throughout
 * the source file if they're not declared inside functions.
 * contrast this with variables defined in functions, 
 * function parameters, or functions declared in functions,
 * which have per-function-call scope.
 *
 * // todo: check these statements (i.e. functions and variables
 * //   declared in functions have per-function scope)
 * 
 *
 * external variables and functions are defined precisely once
 * among all source files for a particular program.
 *
 * the variables declared here are defined in stack_vars.c
 */

extern int sp; /* next free stack position */
extern double val[]; /* stack of values */

void
push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else {
		printf("error: stack full, cant push %g\n", f);
		exits("stack full");
	}
}

double
pop(void)
{
	if(sp > 0)
		return val[--sp];
	else {
		exits("stack empty");
		return 0.0;
	}
}
