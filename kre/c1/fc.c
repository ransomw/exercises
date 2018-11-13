#include <u.h>
#include <libc.h>
#include <stdio.h>

#define LOWER	0
#define UPPER	300
#define STEP	20

/**
 * print Fahrenheit-Celsisus table
 * - cast to floating-point version 
 * - for() loop
 * - preprocessor #define s
 *   (note '#define\s<name>\t<val>' format)
 */
void
main (void)
{
	int fahr;

	/* for(<init>; <cond>; <inc>) { <body> }
	 * eval <init> once, then
	 * 1. eval <cond>. if true run <body>, otherwise continue
	 * 2. eval <inc>
	 * 3. goto 1. */
	for(fahr = LOWER; fahr <= UPPER; fahr += STEP){
		/* in any context where it's permissable to use
		 * a value of a given type, one may use an expression
		 * of that type.
		 * here, the expression for celsius is an example of
		 * the general rule. */
		printf("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr-32));
	}

	exits(0);
}
