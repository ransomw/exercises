#include <u.h>
#include <libc.h>

/* demonstrate syscall dup() as used by the shell to implement
 * input redirection as in `cat < NOTICE`.
 *
 * when called with file descriptors corresponding to open Chans,
 * dup(fda, fdb) takes Chan pointed to by fda in the current
 * process and makes fdb point to that Chan as well instead of
 * the channel it was currently pointing at, as if close(fdb)
 * had been called.
 *
 * if fdb is -1, a new file descriptor is allocated and returned
 * by dup().  other use cases are described in the manual.
 */

void
main(void)
{
	int fd;

	/* the shell calls fork() to avoid mucking about
	 * with its own stdio
	 */
	switch(fork()) {
	case -1:
		sysfatal("fork failed");
	case 0:
		fd = open("NOTICE", OREAD);
		/* replace stdin with the file */
		dup(fd, 0);
		/* since stdin is now pointing to the file,
		 * the file descriptor returned by open()
		 * can be closed.  this doesn't close the Chan.
		 *
		 * ??? is the kernel doing garbage collection
		 * on Chans or what?
		 */
		close(fd);
		/* now, when cat reads from stdin, it's reading
		 * from the file
		 */
		execl("/bin/cat", "cat", nil);
		sysfatal("exec: %r");
	default:
		waitpid();
	}
	exits(nil);
}

/* output redirections are similar: create() is used
 * instead of open()
	fd = create("outfile", OWRITE, 0664);
	dup(fd, 1);
	close(fd);
 * so in particular `aprog <afile >afile`
 * will truncate afile (via create()) before aprog exec()s
 */
