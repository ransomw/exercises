#include <u.h>
#include <libc.h>

void printnettransaddr(char *addr);

void
main(void)
{
	static char addrstr[] = "tcp!*!9988";
	int cfd;
	char dir[40];

	printnettransaddr(addrstr);

	/* cfd is the interfaces ctl file */
	cfd = announce(addrstr, dir);
	if(cfd < 0)
		sysfatal("announce: %r");
	print("announced in %s\n", dir);
	for(;;)
		sleep(1000);
}

/**
 * all the following
 * lifted out of /sys/src/libc/9sys/announce.c
 */

enum
{
	Maxpath=	256,
};

static int nettrans(char*, char*, int na, char*, int);

/* this is the beginning of announce() itself */
void
printnettransaddr(char *addr)
{
	char netdir[Maxpath];
	char naddr[Maxpath];

	if(nettrans(addr, naddr, sizeof(naddr), 
			netdir, sizeof(netdir)) < 0)
		return;

	print("naddr: %s\n", naddr);
	print("netdir: %s\n", netdir);
}

/** verbatim copy */

/*
 *  perform the identity translation (in case we can't reach cs)
 */
static int
identtrans(char *netdir, char *addr, char *naddr, int na, char *file, int nf)
{
	char proto[Maxpath];
	char *p;

	USED(nf);

	/* parse the protocol */
	strncpy(proto, addr, sizeof(proto));
	proto[sizeof(proto)-1] = 0;
	p = strchr(proto, '!');
	if(p)
		*p++ = 0;

	snprint(file, nf, "%s/%s/clone", netdir, proto);
	strncpy(naddr, p, na);
	naddr[na-1] = 0;

	return 1;
}



/*
 *  call up the connection server and get a translation
 */
static int
nettrans(char *addr, char *naddr, int na, char *file, int nf)
{
	int i, fd;
	char buf[Maxpath];
	char netdir[Maxpath];
	char *p, *p2;
	long n;

	/*
	 *  parse, get network directory
	 */
	p = strchr(addr, '!');
	if(p == 0){
		werrstr("bad dial string: %s", addr);
		return -1;
	}
	if(*addr != '/' && *addr != '#'){
		strncpy(netdir, "/net", sizeof(netdir));
		netdir[sizeof(netdir) - 1] = 0;
	} else {
		for(p2 = p; p2 > addr && *p2 != '/'; p2--)
			;
		i = p2 - addr;
		if(i == 0 || i >= sizeof(netdir)){
			werrstr("bad dial string: %s", addr);
			return -1;
		}
		strncpy(netdir, addr, i);
		netdir[i] = 0;
		addr = p2 + 1;
	}

	/*
	 *  ask the connection server
	 */
	snprint(buf, sizeof(buf), "%s/cs", netdir);
	fd = open(buf, ORDWR);
	if(fd < 0)
		return identtrans(netdir, addr, naddr, na, file, nf);
	if(write(fd, addr, strlen(addr)) < 0){
		close(fd);
		return -1;
	}
	seek(fd, 0, 0);
	n = read(fd, buf, sizeof(buf)-1);
	close(fd);
	if(n <= 0)
		return -1;
	buf[n] = 0;

	/*
	 *  parse the reply
	 */
	p = strchr(buf, ' ');
	if(p == 0)
		return -1;
	*p++ = 0;
	strncpy(naddr, p, na);
	naddr[na-1] = 0;

	if(buf[0] == '/'){
		p = strchr(buf+1, '/');
		if(p == nil)
			p = buf;
		else
			p++;
	}
	snprint(file, nf, "%s/%s", netdir, p);
	return 0;
}
