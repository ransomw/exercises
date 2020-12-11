#include <u.h>
#include <libc.h>

/* assumes "afile" exists in the same directory as this program.
 * xd(1) can be used to give hexdumps of afile before and after
 * to demonstrate what the program does.
 *
 * under the hood, file operations are implemented using 9P
 * communication over a Chan, as defined in
 * /sys/src/9/port/portdat.h
 * Chan.offset, Chan.mode, and Chan.path.s
 * contain the offset, mode, and filename, resp.
 */

void
main(void)
{
	char msg[] = "hiya\n";
	char othermsg[] = "ya'll\n";
	int fd;

	fd = open("afile", OWRITE);
	/* write msg to the beginning of the file:
	 * open() sets the offset to zero.
	 */
	write(fd, msg, strlen(msg));
	/* write other msg to the file beginning at the current
	 * offset -- namely, beginning where the previous call
	 * to write ended.
	 */
	write(fd, othermsg, strlen(othermsg));
	close(fd);
	exits(nil);
}
