#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ape/limits.h>
// todo: not present even in ape ..
//   .. also, floating-point is a hassle, so do this later
/* #include <float.h> */

void print_limits(void);

void
main(void)
{
	char c_char, p_char;
	int c_int, p_int;

	printf("limits.h values\n");
	printf("---------------\n");
	print_limits();
	printf("\n");

	printf("computed values\n");
	printf("---------------\n");
	for(c_char = p_char = 0;
		c_char > p_char || p_char == 0;
		++c_char)
		p_char = c_char;
	printf("%12d is maximum value of char\n", p_char);
	for(c_char = p_char = 0;
		c_char < p_char || p_char == 0;
		--c_char)
		p_char = c_char;
	printf("%12d is minimum value of char\n", p_char);

	for(c_int = p_int = 0;
		c_int > p_int || p_int == 0;
		++c_int)
		p_int = c_int;
	printf("%12d is maximum value of int\n", p_int);
	for(c_int = p_int = 0;
		c_int < p_int || p_int == 0;
		--c_int)
		p_int = c_int;
	printf("%12d is minimum value of int\n", p_int);

	// todo: the rest (compute already noticable)

	exits(0);
}

void
print_limits(void)
{
	printf("%12d bits in a char\n", CHAR_BIT);
	printf("%12d is maximum value of char\n", CHAR_MAX);
	printf("%12d is minimum value of char\n", CHAR_MIN);
	printf("%12d is maximum value of int\n", INT_MAX);
	printf("%12d is minimum value of int\n", INT_MIN);
	printf("%12ld is maximum value of long\n", LONG_MAX);
	printf("%12ld is minimum value of long\n", LONG_MIN);
	printf("%12d is maximum value of signed char\n", SCHAR_MAX);
	printf("%12d is minimum value of signed char\n", SCHAR_MIN);
	printf("%12d is maximum value of short\n", SHRT_MAX);
	printf("%12d is minimum value of short\n", SHRT_MIN);
	printf("%12u is maximum value of unsigned char\n", UCHAR_MAX);
	printf("%12u is maximum value of unsigned int\n", UINT_MAX);
	printf("%12u is maximum value of unsigned long\n", ULONG_MAX);
	printf("%12u is maximum value of unsigned short\n", USHRT_MAX);
}

/* - basic data types -
 * char - single byte.
 *	holds one character in local character set
 * int - an integer.
 *	machine-dependent, typically "reflecting natural size of
 *	an integer on the host machine"
 * float - single-precision floating point
 * double - double-precision floating point
 */

/* - data type qualifiers -
 * short, long - apply to integers as in
 *		short int i; long int j;
 * 	and specify the number of bits set aside for storage:
 *	- short specifies at least 16 bits, long at least 32
 *	- short <= unqualified int <= long, machine-dep otherwise
 * 	long may additionally be applied to double
 *		long double d;
 * 	to specify extended-precision floating point
 * (all these *-precisions are impl defined with each <= the next)
 * signed, unsigned - apply to char or int:
 *	- unsigned means the value is non-negative and follows
 *		arithmetic mod 2^n
 *	- signed allows negative values under mach-dep spec
 *		(often two's compliment)
 *	whether plain chars are signed is mach-dep.
 *	printable chars are positive.
 */
