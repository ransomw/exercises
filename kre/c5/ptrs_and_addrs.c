#include <u.h>
#include <libc.h>
#include <stdio.h>

/* the C language relies on its host system to present main memory
 * as a linear array of numerical addresses where variables
 * used by the program (not the program itself) are stored.
 *
 * pointers are variables that contain addresses where other
 * variables are stored, pictorially
                ____________________
              /                      \
             ||                      ||
         p:  ||                  c:  \/
---------------------------------------------------
        |   |   |                |   |   |   |   |
  ...   | | | | |      ...       | | | | | | | | | ...		
        |   |   |                |   |   |   |   |		
---------------------------------------------------
 *
 * p is a pointer (two memory addresses) referring to
 * the value, c (stored in four memory addresses).
 *
 * the number of addresses used to store a pointer is
 * a constant that varies from machine to machine,
 * and the number of address to store a value (char, int, etc.)
 * varies according to the value's type.
 *
 * for now, note that p, the pointer's, value, a single memory
 * address, refers collectively to *all* the memory addresses
 * containing the value of the variable c.
 */


void
main(void)
{
	int x = 1, y = 2;
	int z[] = {3, 4, 5};
	/* the syntax for declaring a pointer variable is
	<type> *<name>
	 * as in
	 */
	int *ip;
	/* this declaration syntax is used in function parameters
	atof(char *)
	 * just as other with other types of declarations.
	 * multiple names can be declared in one statement
	 */
	int *iq, *iptr, i;

	/* the address of a variable (or "object" in the text,
	 * since the use of pointers sometimes resembles OOP),
	 * can be accessed with the `&` operator, as in
	 */
	ip = &x;
	/* ip now contains the address of the variable x, or
	 * we can say, "ip is a pointer to x."
	 *
	 * in the other direction, the `*` "indirection" operator
	 * is used to "dereference" a pointer, that is
	 * to get the value stored at the address contiained
	 * in the pointer variable, as in
	 */
	printf("%d\n", y); /* y is 2 */
	y = *ip; /* y now contains the value referenced by ip */
	printf("%d\n\n", y); /* ip is a pointer to x == 1 */
	/* although the syntax to declare pointers and
	 * to dereference them is similar, there are two
	 * distinct meanings.
	 *
	 * dereferencing can be used on the other side of the
	 * assigment operator as well.
	 */
	printf("%d\n", x);
	*ip = 0;
	printf("%d\n\n", x);

	/* addresses of variables in arrays can be accessed
	 * with the unary `&` just as named values can.
	 */
	ip = &z[1];
	for(i = 0; i < 3; i++)
		printf("%d ", z[i]);
	printf("\n");
	*ip = 27;
	for(i = 0; i < 3; i++)
		printf("%d ", z[i]);
	printf("\n\n");

	/* as far as precendence goes, the unary `&` and `*`
	 * are applied before arithmetic operators, so
	 * parens can be minimized in many calculations
	 */
	x = 1, ip = &x;
	*ip += 1; /* 2 */
	++*ip; /* 3 */
	/* although parentheses are still necessary
	 * to clarify associativity in expressions like
	 */
	(*ip)++; /* 4 */
	/* whereas
	*ip++
	 * would increment the value of the pointer (the address)
	 * rather than the value (of x) referred to by the pointer
	 */
	printf("%d\n\n", x);

	/* and just as with any variable, pointers
	 * can be assigned values of the same type
	 */
	iq = ip;
	iptr = iq;
	++*iptr; /* 5 */
	printf("%d\n", x);

	exits(0);
}

/*
since pointers are declared with a <type>,
the compiler can keep track of how many memory addresses
a pointer refers to, even though its runtime value contains
only a single memory address.
todo: check index to make sure the preceeding is even true.

the exception to this idea is when a pointer has type void.
in the case of a `void *ptr;` declaration, `ptr` can hold any
address, but it can't be dereferenced with `*ptr`,
because the type information (how many addresses the value
is stored in) isn't known.
*/
