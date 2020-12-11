#include <u.h>
#include <libc.h>

/* print() is a wrapper around write()
 *
 * use the `sig` command to see
term% sig write
	long write(int fd, void *buf, long nbytes)
 * the first argument is a *file descriptor*,
 * an index (0-n) into a table (i.e. pointer array,
 * probably) that exists on a per-process basis.
 * entries in the file descriptor table correspond to open files.
 */

void
main(void)
{
	char msg[] = "hello\n";
	int l;

	l = strlen(msg);
	write(1, msg, l);
	exits(nil);
}
