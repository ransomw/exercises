#include <u.h>
#include <libc.h>

/* poll a file for changes by checking its modify time
 * (as opposed to a designated function like select())
 *
 * recall dirstat() from c3/stat.c
 * specifically, dirstat() applies to files as well as
 * directories.
 *
 * run this program like
	term% touch afile ; mk poll.out ; poll.out afile
 * then
	term% echo asdf >> afile
 * in order to see it detect changes.
 */

void
main(int argc, char *argv[])
{
	Dir *d;
	ulong mtime, nmtime;

	if(argc != 2) {
		fprint(2, "usage %s file\n", argv[0]);
		exits("usage");
	}
	d = dirstat(argv[1]);
	if (d == nil)
		sysfatal("dirstat: %r");
	mtime = d->mtime;
	free(d);
	do {
		/* calling sleep between polls is advisable
		 * as usual: it prevents burning too many cycles
		 * while waiting on incoming.
		 */
		sleep(1000);
		d = dirstat(argv[1]);
		if(d == nil)
			break;
		nmtime = d->mtime;
		free(d);
	} while(nmtime == mtime);
	print("%s changed\n", argv[1]);

	exits(nil);
}
