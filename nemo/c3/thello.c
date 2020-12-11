#include <u.h>
#include <libc.h>

/* this is pretty much the same as fhello.c,
 * except the file is opened with the additional OTRUNC flag
 * to truncate the file.
 * this option causes the file's existing contents to be
 * set to empty upon open.
 */

void
main(void)
{
	char msg[] = "hiya\n";
	char othermsg[] = "ya'll\n";
	int fd;

	fd = open("afile", OWRITE | OTRUNC);
	write(fd, msg, strlen(msg));
	write(fd, othermsg, strlen(othermsg));
	close(fd);
	exits(nil);
}
