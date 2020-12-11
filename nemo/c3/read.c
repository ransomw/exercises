#include <u.h>
#include <libc.h>
#define NBYTES	8

/* read some bytes from stdin, write to stdout */

void
main(void)
{
	char buf[NBYTES];
	int n;

	/* provide a maximum number of bytes to read,
	 * return number of bytes read
	 */
	n = read(0, buf, sizeof buf);
	write(1, buf, n);
	exits(nil);
}
