#include <u.h>
#include <libc.h>
#include <bio.h>

void
main(void)
{
	Biobuf abin, about;
	Biobuf *bin = &abin, *bout = &about;
	char *line;
	int len;

	/* Binit() initializes Biobuf s from file descriptors.
	 * it doesn't allocate memory for them, hence
	 * the dereferencing above.
	 */
	Binit(bin, 0, OREAD);
	Binit(bout, 1, OWRITE);
	while(line = Brdline(bin, '\n')) {
		len = Blinelen(bin);
		Bwrite(bout, line, len);
		/* with the following line uncommented,
		 * the program prints lines as they're
		 * read in.
		 * with it commented out, it waits 'til
		 * EOF before printing anything.
		 */
	//	Bflush(bout);
	}
	
	Bterm(bin);
	Bterm(bout);

	exits(nil);
}
