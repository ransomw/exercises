#include <u.h>
#include <libc.h>
#include <plumb.h>

/* demonstrate the C api to get plumber(4) messages.
 * run it with the name of a port as a parameter.
 * get messages like
msg: wdir='/usr/glenda/mtmp' data'ghostintheminesweepershell.back.png' addr='none'
 * upon highlighting a file name and clicking 'plumb'
 * in a rio window, supposing the file name matches a
 * rule in /mnt/plumb/rules that'll route it to the port
 * param of this program.
 *
 * there are also plumbsend() and plumbsendtext() functions
 * to send messages discussed in plumb(2).
 * use and interrupt note via the Delete button to exit.
 */

void
main(int argc, char *argv[])
{
	int fd;
	Plumbmsg *m;
	char *addr;

	if(argc != 2) {
		fprint(2, "usage %s port\n", argv[0]);
		exits("usage");
	}
	fd = plumbopen(argv[1], OREAD);
	if(fd < 0)
		sysfatal("%s port: %r", argv[1]);
	while(m = plumbrecv(fd)) {
		addr = plumblookup(m->attr, "addr");
		if(addr == nil)
			addr = "none";
		print("msg: wdir='%s' data'", m->wdir);
		write(1, m->data, m->ndata);
		print("' addr='%s'\n", addr);
		plumbfree(m);
	}
	fprint(2, "plumbrecv: %r");
	close(fd);

	exits(nil);
}
