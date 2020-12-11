#include <u.h>
#include <libc.h>

/* semantics of the read() system call vary from file to file.
 * we've already seen that the read() system call on /dev/cons
 * returns one line at a time.
 *
 * read() on directories preserves directory entry boundaries:
 * only whole directory entries are read at a time.
 *
 * seek() is not allowed on directories.
 */

void
main(void)
{
	char buf[256];
	int fd, n, i;

	fd = open(".", OREAD);
	
	for(i = 0; i < 3; i++) {
		n = read(fd, buf, sizeof buf);
		print("\n*\t%d\n", n);
		write(1, buf, n);
	}

	exits(nil);
}
