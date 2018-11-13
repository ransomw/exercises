#include <u.h>
#include <libc.h>
#include <stdio.h>

enum fn_enum {ASDF = 1, QWER = 11};

/* although it's legal to specify an enum 
 * in a function prototype..
 */
void enum_fn(fn_enum);

void
main(void)
{
	/* enumeration constants are lists of named values */
	enum boolean { NO, YES };
	/* values are integers, and while names need be distinct,
	 * duplicate values are allowed.
	 */
	enum escapes { BELL = '\a', MA_BELL = '\a' };
	/* if a list item's value is omitted,
	 * its value is always the increment 
	 * of the previous item's value.
	 */
	enum ordinals { FIRST = 1, SECOND, THIRD = 9, FOURTH = 2};

	/* by default, values are successive integers starting at 0 */
	printf("%d %d\n", NO, YES);

	printf("%c%c\n", BELL, MA_BELL);

	printf("%d %d %d %d\n",
		FIRST, SECOND, THIRD, FOURTH);

	enum_fn(ASDF);
	enum_fn(11);
	/* .. there's no type-checking of parameter's passed .. */
	enum_fn(12);

	exits(0);
}

/* .. and enum name cannot be used in place of int type
 *    in function definitions.
 */
void
enum_fn(int x)
{
	printf("%d\n", x);
}
