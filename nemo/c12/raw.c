#include <u.h>
#include <libc.h>

/* this program is used to demonstrate the difference between
 * "raw" and "cooked" keyboard input.  in labs plan 9, these
 * inputs are provided by '#c', while in 9front, they're served
 * by kbdfs(8).  both provide a `consctl` file, and writing to
 * this file can enable raw mode.
 *
 * in a rio window on 9front enabling raw mode mostly means that
 * reads return a character at a time rather than a line at a time.
 * in particular, entering runes (unicode) as described in keyboard(6)
 * still functions as normal.
 */

void
usage(void)
{
	fprint(2, "usage: %s [-r]\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	char buf[512];
	int raw = 0;
	int cfd = -1;
	int nr;

	ARGBEGIN {
	case 'r':
		raw++;
		break;
	default:
		usage();
	}ARGEND;
	if(argc != 0)
		usage();

	if(raw) {
		cfd = open("/dev/consctl", OWRITE);
		write(cfd, "rawon", 5);
	}

	for(;;) {
		nr = read(0, buf, sizeof(buf)-1);
		if(nr <= 0)
			break;
		buf[nr] = '\0';
		print("[%s]\n", buf);
	}
	if(raw)
		close(cfd);
	exits(nil);
}
