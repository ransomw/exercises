#include <u.h>
#include <libc.h>

void printconninfo(int fd);

void
main(int argc, char *argv[])
{
	int fd, srvfd;
	char *addr;
	char fname[128];
	char dir[128];

	if(argc != 2) {
		fprint(2, "usage: %s netaddr\n", argv[0]);
		exits("usage");
	}

	/* ensure full <net>!<system>!<service> address,
	 * adding default <net> and <service> if they're
	 * not present.
	 */
	addr = netmkaddr(argv[1], "tcp", "9fs");
	/* wraps file-io necessary to open a connection,
	 * returning a file descriptor for the connection's data
	 * file.  cf. mget.rc, particularly csquery usage.
	 */
	fd = dial(addr,
			/* local address for protocols that allow */
			nil,
			/* return value by pointer: path to conn
			 * e.g. /net/tcp/0
			 */
			dir,
			/* return value by pointer: int *cfdp
			 * the connection's ctl file
			 */
			nil);
	if(fd < 0)
		sysfatal("dial: %s: %r", addr);
	print("dial: %s\n", dir);
	printconninfo(fd);

	/* seprint is sscanf-alike */
	seprint(fname, fname+sizeof(fname), "/srv/%s", argv[1]);
	/* this is the srv(3) install described in c5/srvecho.c.
	 * it gives the kernel a reference to the fd Chan.
	 */
	srvfd = create(fname, OWRITE, 0664);
	if(srvfd < 0)
		sysfatal("can't post %s: %r", fname);
	if(fprint(srvfd, "%d", fd) < 0)
		sysfatal("can't post file descriptor");
	close(srvfd);
	close(fd);
	exits(nil);
}

/* access data about a network connection using either the
 * the data or ctl file descriptor
 */
void
printconninfo(int fd)
{
	NetConnInfo *i;

	i = getnetconninfo(nil, fd);
	if(i == nil)
		sysfatal("can't get info: %r");
	print("info: dir:\t%s\n", i->dir);
	print("info: root:\t%s\n", i->root);
	print("info: spec:\t%s\n", i->spec);
	print("info: lsys:\t%s\n", i->lsys);
	print("info: lserv:\t%s\n", i->lserv);
	print("info: rsys:\t%s\n", i->rsys);
	print("info: rserv:\t%s\n", i->rserv);
	print("info: laddr:\t%s\n", i->laddr);
	print("info: raddr:\t%s\n", i->raddr);
	freenetconninfo(i);
}
