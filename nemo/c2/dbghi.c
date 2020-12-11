#include <u.h>
#include <libc.h>

/* this program intentionally crashes
 * in order to demonstrate debugger functionality
 */

void
main(int argc, char *argv[])
{
	print("hi ");
	print(argv[1]);
	exits(nil);
}
