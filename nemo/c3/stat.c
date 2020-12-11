#include <u.h>
#include <libc.h>

/* C api for `ls`-like functionality is provided by
 * dirstat(), which returns a Dir pointer.
 * Dir is a structure containing the info about the file
 * available in the directory containing the file.
 *
 * e.g. for adir/afile, dirstat("afile") contains data
 *	about afile available via `cat adir` or `xd -s adir`
 */

void
main(void)
{
	Dir *d;
	int fd;

	d = dirstat("stat.c");
	print("filename: %s\n", d->name);
	print("filemode: 0%o\n", (int) d->mode);
	print("filesize: %d bytes\n", (int) d->length);
	/* note that dirstat() calls malloc(),
	 * so it's necessary to free the memory after use.
	 *
	 * all memory is allocated in a single malloc() call,
	 * so a single free() call suffices
	 */
	free(d);

	/* extracurricular directory bits via BurnZeZ:
	 * prefer using QTDIR to test is directory
	 */
	d = dirstat("stat.c");
	print("filename: %s\n", d->name);
	print("mode: 0x%x\n", (int) d->mode);
	print("dirbits: %x\n", (int) (0x80000000 & d->mode));
	print("dir bool: %x\n", (int) (d->qid.type & QTDIR));
	free(d);
	d = dirstat("adir");
	print("filename: %s\n", d->name);
	print("mode: 0x%x\n", (int) d->mode);
	print("dirbits: %x\n", (int) (0x80000000 & d->mode));
	print("dir bool: %x\n", (int) (d->qid.type & QTDIR));
	free(d);

	/* the dirfstat() variety of dirstat() accepts
	 * file descriptors instead of filenames
	 */
	fd = open("stat.c", OREAD);
	d = dirfstat(fd);
	close(fd);
	print("filename: %s\n", d->name);
	free(d);

	/* there are also dirwstat() and dirfwstat()
	 * functions to write Dir structs into the system.
	 */

	exits(nil);
}
