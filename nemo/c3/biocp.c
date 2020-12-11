#include <u.h>
#include <libc.h>
#include <bio.h>

/* compare with bcp.c
 * this program implements file copying using bio.h
 * instead of system calls to read and write files.
 *
 * the advantage here is speed:  even with the internal
 * buffer, buf, using read() and write() directly is slow
 * on large files.  no matter what the internal buffer size
 * is, using bio.h results in copying at about the same speed.
 * without bio.h, copying speed is much slower with smaller
 * internal buffers.
 *
 * care must be taken to flush output when using buffers.
 * Bterm() flushes output before closing buffers.
 * Bflush() can be used to flush without closing.
 */

static void
usage(void)
{
	fprint(2, "usage: %s [-b bufsz] infile outfile\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	char *buf;
	long nr, bufsz = 8 * 1024;
	Biobuf *bin, *bout;

	ARGBEGIN{
	case 'b':
		bufsz = atoi(EARGF(usage()));
		break;
	default:
		usage();
	}ARGEND;
	if(argc != 2)
		usage();

	buf = malloc(bufsz);
	if(buf == nil)
		sysfatal("no more memory");

	bin = Bopen(argv[0], OREAD);
	if(bin == nil)
		sysfatal("%s: %s: %r", argv0, argv[0]);
	bout = Bopen(argv[1], OWRITE);
	if(bout == nil)
		sysfatal("%s: %s: %r", argv0, argv[1]);

	while((nr = Bread(bin, buf, bufsz)) > 0)
		Bwrite(bout, buf, nr);

	Bterm(bin);
	Bterm(bout);

	exits(nil);
}
