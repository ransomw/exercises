#include <u.h>
#include <libc.h>
#define MINDIR	40

/* concurrent echo server
 * cf. netecho.c
 * in fact, this program introduces no additional networking
 * concepts.  it uses some existing multiprocessing concepts
 * together with the networking concepts demonstrate by netecho.c
 */

void
main(void)
{
	static char addrstr[] = "tcp!*!9988";
	int afd, lfd, dfd;
	long nr;
	char adir[MINDIR], ldir[MINDIR], buf[1024];

	print("connect to '%s' with telnet(1)", addrstr);
	print(" where '*' is probably %s", getenv("sysname"));
	print(" after announce\n");
	print("try it with two connections at once\n");

	afd = announce(addrstr, adir);
	if(afd < 0)
		sysfatal("announce: %r");
	print("announced in %s (cfd=%d)\n", adir, afd);
	for(;;) {
		/* on each incoming connection */
		lfd = listen(adir, ldir);
		if(lfd < 0)
			sysfatal("listen: %r");
		switch(fork()) {
		case -1:
			sysfatal("fork: %r");
		case 0: /* recall, this is the child process */
			/* and it's good practice to close
			 * unused file descriptors
			 */
			close(afd);

			dfd = accept(lfd, ldir);
			if(dfd < 0)
				sysfatal("can't accept: %r");

			close(lfd);
			print("accepted call at %s\n", ldir);
			for(;;) {
				nr = read(dfd, buf, sizeof buf);
				if(nr <= 0)
					break;
				print("got '%s' from client\n", buf);
				write(dfd, buf, nr);
			}
			print("ended call at %s\n", ldir);
			/* calling exits() from a process-specific
			 * control flow is a variation on
			 * multiprocess programming that hasn't
			 * been seen yet.
			 *
			 * this program's parent process terminates
			 * on a note.
			 *
			 * this is conceptually similar to return;
			 * statements ending control flows within
			 * functions:  exits() ends control flow
			 * within a process
			 */
			exits(nil);
		default:
			close(lfd);
		}
	}
}
