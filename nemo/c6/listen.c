#include <u.h>
#include <libc.h>
#define MINDIR	40

/* cf. ann.c */

/* while announce() operates by writing messages to
 * the /ctl file of a connection created by reading
 * /clone in the protocol (e.g. tcp) root directory,
 * listen() uses the /listen file in the conn dir.
 *
 * open()ing /listen doesn't return until a call is
 * recved at the announce()d addr.  when open()
 * returns, it returns the a file descriptor to
 * the /ctl file to a *new* connection, and the
 * first read from this /ctl file (also performed by
 * listen()) provides the connection number to the
 * calling process such that ldir in the following
 * has the proper value.
 *
 * to reiterate, there are two connection directories:
 * - the first that announces it can accept incoming connections
 * - the second that is created upon an incoming connection
 *	and reported to the first via the /listen file
 */

void
main(void)
{
	static char addrstr[] = "tcp!*!9988";
	/* variables to hold values from announce and listen */
	int afd, lfd;
	char adir[MINDIR], ldir[MINDIR];

	afd = announce(addrstr, adir);
	if(afd < 0)
		sysfatal("announce: %r");
	print("announced in %s (cfd=%d)\n", adir, afd);
	lfd = listen(adir, ldir);
	print("attending call in %s (lfd=%d)\n", ldir, lfd);
	for(;;)
		sleep(1000);
}
