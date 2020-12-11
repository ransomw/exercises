#include <u.h>
#include <libc.h>
#define NBYTES	8

void
main(void)
{
	char buf[NBYTES];
	int fdin, fdout, n;


	/* in readcons_v1.c, the same file descriptor
	 * was used to read and write.
	 * this program differs by opening the same
	 * file with two file descriptors, one for reading
	 * and one for writing.
	 *
	 * check /proc/<pid>/fd for a list of file-descriptors.
	 */
	fdin = open("/dev/cons", OREAD);
	fdout = open("/dev/cons", OWRITE);
	n = read(fdin, buf, sizeof buf);
	write(fdout, buf, n);
	close(fdin);
	close(fdout);
	exits(nil);
}
