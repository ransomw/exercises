#include <u.h>
#include <libc.h>
#define MAXERR	128

/* system calls set an error string and return -1
 * if they fail.
 */

void
main(void)
{
	char errorstr[MAXERR];

	if(chdir("nexist") < 0) {
		/* the %r formatter can be used to access
		 * the error string.
		 */
		print("chdir failed %r\n");
	}
	/* as can rerrstr() */
	rerrstr(errorstr, MAXERR);
	print("yep, it failed ");
	print(errorstr);
	print("\n");

	/* the error-string is stored in a per-process
	 * buffer, and the process can write to it just as
	 * the system can.
	 *
	 * like printf(),
	 */
	werrstr("some %c%c%c", 'e', 'r', 'r');

	/* sysfatal does and print() and exits() all-in-one */
	sysfatal("ererer %r");
}
