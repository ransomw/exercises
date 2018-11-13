#include <u.h>
#include <libc.h>
#include <stdio.h>

/* pointers and arrays have a close correspondence
 * wherein array indexing turns out to be syntatic sugar
 * for pointer arithmetic.
 */

int getninth(int[]);
int mystrlen(char *);
int getprev(int *);

void
main(void)
{
	int i, *aptr;
	/* an array is a contiguous segment of the linear
	 * abstraction of main memory used by C
	 * (cf. pts_and_addrs.c)
	 */
	int a[10];
	/* we've previously used indices to access values
	 * stored in that segment as in
	 */
	a[0] = 1; a[1] = 1;
	/* and we've already noted that the address of
	 * array values can be stored in a pointer,
	 * just like the address of any other value
	 */
	aptr = &a[1];

	/* the novel idea in this section is that adding
	 * and subtracting integers from a pointer to an
	 * element of an array "moves" the pointer forward
	 * and backward along the array.
	 *
	 * that is, although the memory address of a pointer
	 * is a number, the compiler understands that adding
	 * an integer to a pointer doesn't literally mean
	 * to increment the memory address by that integer
	 * amount:  just as implicit type casts can occur
	 * in arithmetic between other types (the common
	 * example seen so far is `i +/- '0'`), they also
	 * occur between integers and pointers.
	 *
	 * specifically, for arrays that aren't of `void` type,
	 * adding or subtracting an integer from a pointer
	 * increases or decreases the pointer's value by
	 * as many addresses in the linear memory model as
	 * that many integer values of the type occupy.
	 * that is,
	 *	p + n
	 * evaluates to
	 *	m*n
	 * to pointer p's value, where m is the number of
	 * addresses required for a single value of p's type.
	 *
	 * as an aside, this is probably considered a functor
	 * when wearing fancy pants.  for those in moderately-
	 * fancy pants such as khulats or bell-bottoms,
	 * here's the beginning of the fibbonaci sequence:
	 */
	while((*(++aptr) = *aptr + *(aptr - 1)) <= 34)
		printf("%d ", *aptr);
	printf("\n");
	/* as a more salient aside,
	 * typecasts can occur from pointers to integers
	 * just as well as from integers to pointers
	 */
	printf("Plan %d\n", aptr - a);

	/* in fact, the name of an array is itself evaluated
	 * to the memory address (the value of a pointer)
	 * in arithmetic expressions.
	 */
	for(i = 0; i < 9; i++)
		printf("%d ", i % 2 ? a[i] : *(a + i));
	printf("\n\n");
	/* the latter two operands to ? above are equivalent.
	 * the compiler immediately translates `array[<expr>]`
	 * to `*(array + (<expr>))`, so we can say that
	 * the former expression is "syntactic sugar" for
	 * the latter.
	 * 
	 * the difference between arrays and pointers is
	 * that the name of an array can't be reassigned
	 * to a different memory address.  an expression such as
		a++;
	 * results in the compiler error 'not an l-value'.
	 * l is for left, meaning the left side of an =
	 * operator.
	 * with regard to function definitions,
	 * `<type> <name>[]` and `<type> *<name>` are
	 * equivalent, however.
	 */
	printf("%d\n", getninth(a));
	/* when an array is passed to a function,
	 * pass-by-value means that it gets cast to a pointer.
	 * here's the example from the text
	 */
	printf("%d\n", mystrlen("asdf"));


	printf("\n");
	/* as a special case of the previous notes on the equivlance
	 * between `a[i]` and `*(a + i)`,
	 * it's possible to use the array index syntax to
	 * dereference pointers.
	 */
	printf("%d\n", aptr[0]);
	printf("%d\n", getprev(&a[9])); /* see below */

	exits(0);
}

int
getninth(int a[])
{
	a += 8;
	return *a;
}

/* as a further consequence of the equivlance between
 * `a[i]` and `*(a + i)`, note that it's possible to
 * use negative indexes into arrays.
 * as with a lot of pointer and array use,
 * it's the programmer's responsibility to avoid
 * accessing memory addresses unintentionally.
 */
int
getprev(int a[])
{
	return a[-1];
}

int
mystrlen(char *s)
{
	int n;

	for(n = 0; *s != '\0'; s++)
		n++;
	return n;
}
