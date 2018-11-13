#include <u.h>
#include <libc.h>
#include <stdio.h>

// todo: determine why two ^D's are necessary to exit
//       when there's not a newline in the stream
/**
 * count characters, second version
 */
void
main(void)
{
	/* dbl precision float for counting even more */
	double nc;

	for(nc = 0; getchar() != EOF; ++nc)
		;
		/* the isolated semi-colon is a /null statement/
		 * necessary according to C's grammar */

	/* %f formats double and float alike */
	printf("%.0f\n", nc);

	exits(0);
}
