#include <u.h>
#include <libc.h>
#define NBYTES	8

/* file descriptors have program-specific offsets.
 * these can be modified with the seek(<fd>, <bytes>, <flag>)
 * function.  <flag> has values - indicating
 * 0 - absolute position from beginning of file
 * 1 - relative to current position in file
 * 2 - absolute position at end of file
 */

void
main(void)
{
	char buf[NBYTES];
	int fdin, fdout, n;

	fdin = open("seek.c", OREAD);
	fdout = open("/dev/cons", OWRITE);

	/* read from beginning of file */
	n = read(fdin, buf, sizeof buf);
	write(fdout, buf, n);
	write(fdout, "---\n", 4);

	/* rewind from current position and read */
	seek(fdin, -(n/2), 1);
	n = read(fdin, buf, sizeof buf);
	write(fdout, buf, n);
	write(fdout, "---\n", 4);

	/* rewind to beginning of file */
	seek(fdin, 0, 0);
	n = read(fdin, buf, sizeof buf);
	write(fdout, buf, n);
	write(fdout, "---\n", 4);

	/* fast-forward to end of file, less buffer size */
	seek(fdin, -(sizeof buf), 2);
	n = read(fdin, buf, sizeof buf);
	write(fdout, buf, n);
	write(fdout, "---\n", 4);

	close(fdin);
	close(fdout);
	exits(nil);
}
