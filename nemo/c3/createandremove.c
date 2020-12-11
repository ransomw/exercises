#include <u.h>
#include <libc.h>

/* demonstrate creating, removing, and checking
 * for existance of files.
 * this version omits syscall error-handling.
 */

void
main(void)
{
	char fname[] = "afile";
	char msg[] = "hiya!\n";
	int fd;

	/* remove the file if it already exists.
	 *
	 * other possibilities include
	 * AWRITE, AREAD, AEXEC
	 */
	if(access(fname, AEXIST) >= 0)
		/* empty directories can be removed
		 * just like files
		 */
		remove(fname);
	/* create a new file */
	fd = create(fname, OWRITE, 0664);
	write(fd, msg, strlen(msg));
	close(fd);

	/* create a new directory.
	 *
	 * writing to a directory isn't permitted.
	 * the directory entry is automatically updated
	 * when files are written into it.
	 * the directory file can be read with `cat` or `xd -c`
	 * just like any other file.
	 *
	 * the thing that distinguishes creating a directory
	 * from creating a file is the DMDIR flag.
	 */
	fd = create("adir", OREAD, DMDIR|0775);
	close(fd);

	exits(nil);
}
