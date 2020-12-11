#include <u.h>
#include <libc.h>

/* in addition to sending notes from one process to another
 * via the kernel as in pnote.c, the kernel itself uses
 * notes to signal exceptional conditions to processes
 */

/*** DO NOT return non-zero values from these handlers **/

/* in fact, NEVER write a catch-all handler.
 * at least ensure that the note doesn't begin with 'sys:',
 * or be very careful when handling notes beginning with 'sys:'.
 */

int handler(void *, char *msg)
{
	print("note: %s\n", msg);
	return 0;
}

int handlerdos(void *, char *msg)
{
	print("note again: %s\n", msg);
	return 0;
}

void
main(void)
{
	int fd, c, zero, res;
	char str[] = {'\0', '\0'};

	/* on other systems, note handlers are used to
	 * remove temporary files.  on Plan 9, the ORCLOSE
	 * flag is used instead.  when the file descriptor
	 * of a file create()d or open()ed with this
	 * flag is closed (at process exit or otherwise),
	 * the file is remove()d
	 */
	fd = create("temp", ORDWR|ORCLOSE, 0664);
	write(fd, "0", 1);
	seek(fd, -1, 1);
	read(fd, &c, 1);
	str[0] = c;
	zero = atoi(str);
	close(fd);
	if(access("temp", AEXIST) >= 0)
		print("this never happens");
	else
		print("yep, it's gone\n");

	/* now observe a note from the kernel */
	atnotify(handler, 1);
	atnotify(handlerdos, 1);
	res = 1 / zero;

	/* BE WARNED
	 * your cpu will catch on fire
	 * before you read these lines
	 */
	print("%d\n", res);

	print("stuf (%r)\n");


	exits(nil);
}
