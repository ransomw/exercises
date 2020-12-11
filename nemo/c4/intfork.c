#include <u.h>
#include <libc.h>

/* fork() creates a copy of the parent program,
 * including all of the parent program's memory segments.
 *
 * fork() does *not* create a copy of Chan structures
 * in the kernel corresponding to file descriptors
 * in the process.  the file descriptors themselves
 * are copied, but they refer to the same Chan in both
 * processes.
 */

void
main(void)
{
	char *buf;
	int i, pid, fd;

	/* setup some values in parent process' memory
	 * segements
	 */
	buf = malloc(1);
	*buf = 'a';
	i = 1;
	fd = create("afile", OWRITE, 0644);

	/* fork the process in twain */
	pid = fork();

	/* modify those values */
	i++;
	(*buf)++;

	/* observe that modifications to memory
	 * occur separately */
	print("%d\n", i);
	print("%c\n", *buf);

	free(buf);

	/* meanwhile, both process write to the same
	 * Chan, hence to the same file
	 */
	if(pid == 0) {
		/* even after close() is called in the
		 * parent process, the file is still open
		 * here:  close() doesn't necessarily
		 * close the Chan.  it closes the current
		 * process's connection with the Chan.
		 */
		sleep(3000);
	//	close(fd);
		/* even without the sleep(),
		 * write() calls are gauranteed to be
		 * atomic up to some buffer size
		 * on the order of kilobytes
		 */
		write(fd, "child\n", 6);
	} else
		write(fd, "parent\n", 7);

	close(fd);

	exits(nil);
}
