#include <u.h>
#include <libc.h>

/* this variant of thello.c creates a *file with holes*
 * by seeking past the end of where bytes are written
 * and writing some bytes.  `xd -s afile` is necessary to
 * distinguish the file created by this program from that
 * created by thello.c -- `cat afile` produces the same output
 * in both cases.
 *
 * zero bytes needn't be stored on disk:  a file with holes
 * can be of larger size than available storage, provided the
 * bytes actually written to the file fit in storage.
 */

void
main(void)
{
	char msg[] = "hiya\n";
	char othermsg[] = "ya'll\n";
	int fd;

	fd = open("afile", OWRITE | OTRUNC);
	write(fd, msg, strlen(msg));
	seek(fd, 32, 0);
	write(fd, othermsg, strlen(othermsg));
	close(fd);
	exits(nil);
}
