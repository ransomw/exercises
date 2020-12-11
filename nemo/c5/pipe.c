#include <u.h>
#include <libc.h>

/* this is a minimal example of the pipe() system call
 * expressed in the shell language as `|`.
 *
 * in the program, the system call pipe() is considered
 * separately: it's used to create a pair of file descriptors
 * such that write()s to one file descriptor may be read()
 * from the other.
 *
 * although the pair of file descriptors setup by pipe()
 * are typically used to pass data between processes after
 * fork() calls, this program doesn't call fork().
 */

void
main(void)
{
	int fd[2];
	char buf[128];
	int nr;

	if(pipe(fd) < 0)
		sysfatal("can't create a pipe: %r");

	write(fd[1], "Hiya,\n", 6);
	write(fd[1], "thur!\n", 6);
	/* as with directories, pipes have their own
	 * read() semantics.  namely, reading from a pipe
	 * 'preserves write() boundaries' in the sense that
	 * the buffer is filled 'til the minimum of the
	 * buffer size param or the last byte written
	 * to the pipe.
	 */
	nr = read(fd[0], buf, 2); /* Hi */
	write(1, buf, nr);
	write(1, "\n*\n", 3);
	nr = read(fd[0], buf, sizeof buf); /* ya,\n */
	write(1, buf, nr);
	write(1, "*\n", 2);
	nr = read(fd[0], buf, sizeof buf); /* thur!\n */
	write(1, buf, nr);

	/* and although it's conventional to write to
	 * the second file descript while reading from the first,
	 * both descriptors are read-write and messages can
	 * travel in either direction.
	 */
	write(fd[0], "hiYA,\n", 6);
	write(fd[1], "stur!\n", 6);
	nr = read(fd[0], buf, sizeof buf);
	write(1, buf, nr);
	nr = read(fd[1], buf, sizeof buf);
	write(1, buf, nr);

	/* after closing one end of the pipe,
	 * read()ing from the other end of the pipe returns
	 * 0 bytes (i.e. EOF.  on plan 9, read() == 0 means EOF).
	 *
	 * in the following, commenting out the close()
	 * causes read() to block.
	 */
	close(fd[1]);
	nr = read(fd[0], buf, sizeof buf);
	assert(nr == 0);

	exits(nil);
}
