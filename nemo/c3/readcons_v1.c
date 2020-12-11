#include <u.h>
#include <libc.h>
#define NBYTES	8

/* use a file-descriptor provided by open(),
 * not one of the standard streams associated with the process
 */

void
main(void)
{
	char buf[NBYTES];
	int fd, n;

	/* /dev/cons is the per-process 'console'
	 * that behaves like stdio from a rio window.
	 *
	 * in 9front, /dev/cons is bound to kbdfs in bootrc,
	 * then rio further virtualizes the file on a
	 * per-window basis.
	 */
	fd = open("/dev/cons",
	/* ORDWR is an integer constant (enum, probably)
	 * meaning that the file ought be opened with
	 * both read and write perms
	 */
			ORDWR);
	n = read(fd, buf, sizeof buf);
	write(fd, buf, n);
	close(fd);
	exits(nil);
}
