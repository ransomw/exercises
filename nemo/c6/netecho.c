#include <u.h>
#include <libc.h>
#define MINDIR	40

/* this is a synchronous echo server */

/* cf. listen.c */

int myaccept(int ctl, char *dir);

void
usage(void)
{
	fprint(2, "usage %s [-m]\n", argv0);
	exits("usage");
}


void
main(int argc, char *argv[])
{
	static char addrstr[] = "tcp!*!9988";
	int mflag = 0;
	int afd, lfd, dfd;
	long nr;
	char adir[MINDIR], ldir[MINDIR], buf[1024];

	ARGBEGIN{
	case 'm':
		mflag = 1;
		break;
	default:
		usage();
	}ARGEND;

	print("connect to '%s' with telnet(1)", addrstr);
	print(" where '*' is probably %s", getenv("sysname"));
	print(" after announce\n");
	/* announce once */
	afd = announce(addrstr, adir);
	if(afd < 0)
		sysfatal("announce: %r");
	print("announced in %s (cfd=%d)\n", adir, afd);
	for(;;) {
		/* on each incoming connection */
		lfd = listen(adir, ldir);
		if(lfd < 0)
			sysfatal("listen: %r");
		/* all accept() does is write 'accept n'
		 * to the newly-created connection's /ctl
		 * file and return a file descriptor for
		 * its data file.
		 *
		 * myaccept() is accept(), except the first
		 * parameter might be negative to indicate
		 * that it's myaccept()'s job to open the
		 * /ctl file in order to write 'accept n'.
		 */
		dfd = myaccept(mflag ? -1 : lfd, ldir);
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
		close(dfd);
	}
}

/**
 * lifted out of announce.c
 */

enum
{
	Maxpath=	256,
};

int
myaccept(int ctl, char *dir)
{
	char buf[Maxpath];
	char buf2[Maxpath];
	char *num;
	long n;
	int ctl2;

	num = strrchr(dir, '/');
	if(num == nil)
		num = dir;
	else
		num++;

	n = snprint(buf, sizeof(buf), "accept %s", num);
	if(ctl >= 0)
	/* ignore return value, network might not need accepts */
		write(ctl, buf, n);
	else {
		/*
		 * this is in order to demonstrate that the
		 * file descriptor returned by open()ing /listen
		 * is actually functionally equivalent to
		 * a file descriptor by open()ing the new
		 * /ctl file created by open()ing /listen.
		 */
		n = snprint(buf2, sizeof(buf2), "%s/ctl", dir);
		ctl2 = open(buf2, ORDWR);
		write(ctl2, buf, n);
		close(ctl2);
	}

	snprint(buf, sizeof(buf), "%s/data", dir);
	return open(buf, ORDWR);
}
