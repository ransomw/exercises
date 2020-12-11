#include <u.h>
#include <libc.h>

/* this program demonstrates srv(3), a kernel device.
 * like all kernel devices it's called #<char>[num], where
 * <char> is any unicode character, and [num] is an optional
 * unsigned integer.  see what it is from the shell by
 * running
	term% ls '#s'
 * just like we can see what the first and second ethernet
 * kernel devices (typically the ethernet plug and wifi) are with
	term% ls '#l0' '#l1'
 * ... the quotes are necessary b/c # is a special character
 * in rc, the shell language.
 *
 * specifically, see that kernel devices are filesystems,
 * each with its own semantics and (as more notable in the 
 * case of ethernet) directory structure.  all are nonetheless
 * filesystems:  trees of names, where each name is
 * a directory or a file. and while each file can have its own
 * read() and write() semantics, the unifying abstraction is
 * that of composing bytestreams.
 *
 * this program explores the semantics of the '#s' device,
 * typically also accessible (more later) by running
	term% ls /srv
 *
 * try it out by running this program and then
	term% echo stuf >> /srv/echo
	term% rm /srv/echo
 * in a different rio window.
 */

void
main(void)
{
	int fd[2];
	int srvfd;
	int secsrvfd;
	char buf[128];
	int nr;

	/* creating a pipe is business as usual.
	 * the thing about #s is that it allows connecting
	 * the pipe to other processes by means other than
	 * a fork() syscall.
	 */
	if(pipe(fd) < 0)
		sysfatal("pipe: %r");

	/* BEGIN install write endpoint */
	/* take this segment of the program as a sequence
	 * of syscalls:  fprint wraps write() in vfprint.
	 * remember that '/srv' is '#s' (for now)
	 * and that create() is a syscall.
	 *
	 * creating a file in #s returns a file descriptor
	 * attached to a special installer Chan.
	 */
	srvfd = create("/srv/echo", OWRITE, 0664);
	if(srvfd < 0)
		sysfatal("can't create at /srv: %r");

	/* a write() to the file descriptor attached
	 * to the installer Chan is expected to contain
	 * another of the current process' file descriptors.
	 * afterward, the kernel keeps a reference to
	 * that other file descriptor's Chan (the
	 * write end of the pipe in this case), call it
	 * the installed Chan.
	 *
	 *	the installer Chan is special.
	 *	the installed Chan is generic.
	 */
	if(fprint(srvfd, "%d", fd[1]) < 0)
		sysfatal("can't post file descriptor: %r");
	/* END install write endpoint */

	/* further writes to the install Chan file descriptor
	 * are errors
	 */
	if(fprint(srvfd, "%d", fd[0]) < 0)
		print("nein!\n");
	if(fprint(srvfd, "%d", fd[1]) < 0)
		print("nein!\n");
	/* so we might as well close it */
	close(srvfd);

	/* just as with fork(), it's good practice to
	 * close pipe endpoints after the current process
	 * is done with them.
	 */
	close(fd[1]);

	/* after install, a new file exists in #s.
	 * opening that file provides *any* process
	 * with a reference to the installed Chan.
	 */
	secsrvfd = open("/srv/echo", OWRITE);
	write(secsrvfd, "hiya\n", 5);
	close(secsrvfd);

	/* so any program that writes to /srv/note
	 * writing to one end of the pipe, and removing
	 * /srv/note closes the installed Chan -- i.e.
	 * the other end of the pipe.
	 */
	for(;;) {		
		nr = read(fd[0], buf, sizeof buf);
		if(nr <= 0)
			break;
		write(1, buf, nr);
	}
	/* if either close(fd[1]) or close(secsrvfd) is removed
	 * above, then rm /srv/note doesn't close the other
	 * end of the pipe:  the installed Chan will stay alive
	 * as long as any process has a reference to it.
	 */
	print("exiting\n");

	exits(nil);
}
