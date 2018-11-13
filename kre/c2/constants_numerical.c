#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	unsigned int uint_x, uint_y, uint_z;

	/* suffixes 'u' or 'U' and 'l' or 'L'
	 * used to qualify int constants as unsigned, long, or both
	 */
	// todo: signed operations ok with unsigned constants?
	printf("int constant suffixes\n%ld %d %lu %d %u\n",
		1234L, 123U, 4321UL, -1u, -1u);

	/* use decimal point or exponential notation
	 * to denote floating-point constant
	 */
	printf("floating-point constants\n%.1f %.2f\n",
		123.4, 1234e-2);

	/* suffixes 'f' or 'F' and 'l' or 'L'
	 * qualify floating-point constants as
	 * float and long double, resp
	 */
	printf("floating-point constant suffixes\n%.1f %.3lf\n",
		321.F, 123.456L);

	/* int constants may also be specified in hex and octal
	 */
	printf("hex constants\n%x %x %d\n",
		/* both upper- and lower-case alpha permitted */
		0x1F, 0x1f, 0x1F);
	printf("octal constants\n%o %d\n",
		0777, 0777);

	/* expressions involving only constants
	 * are possibly evaluated at compile-time
	 * and so ought be considered the same as constants
	 */
	uint_x = -1u + -1u;
	/* evaluated at runtime */
	uint_y = uint_x + uint_x;
	printf("%d %u %d %u\n",
		uint_x, uint_x, uint_y, uint_y);


	exits(0);
}
