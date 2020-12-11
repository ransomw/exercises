#include <u.h>
#include <libc.h>

/* this is a quick demo of the RFNOTEG flag to rfork() */

void
main(void)
{
	int i;

	/* with this line present, sending a note
	 * (e.g. via pressing the <delete> key in the process's
	 * rio window) to the parent process's note group
	 * keeps the process alive, because this process gets
	 * its own note group.
	 *
	 * this is the sort of thing that's useful for daemons
	 */
	rfork(RFNOTEG);
	for(i = 0; i < 5; i++) {
		sleep(1000);
		print("%d ", i);
	}
	print("\n");
	exits(nil);
}
