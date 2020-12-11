#include <u.h>
#include <libc.h>

/* this program introduces the rendezvous() system call,
 * a means of synchronization and concurrent communication
 * across process boundaries.
 *
 * it takes a tag and a value (both void pointers) as parameters.
 * rendezvous() pauses the calling process until or unless
 * there's another process that will call or has called
 * rendezvous() with the same tag.
 * rendezvous()'s return value is the the value passed to
 * this system call by the other process.
 */

int
someinit(void)
{
	sleep(1000);
	return -1; // 0 or -1
}

void
someservice(void)
{
	sleep(3000);
}

void
main(void)
{
	int childsts;
	switch(rfork(RFPROC|RFNOTEG|RFNOWAIT)) {
	case -1:
		sysfatal("rfork: %r");
	case 0:
		
		if(someinit() < 0) {
			/* note the idiomatic choice of tag:  a pointer
			 * to the function containing the processes' fork()
			 */
			rendezvous(&main, (void *) -1);
		} else {
			rendezvous(&main, (void *) 0);
		}
		someservice();
		exits(nil);
	default:
		/* rendezvous() isn't just a meeting point --
		 * it's a handoff, a trade, of values
		 */
		childsts = (int) rendezvous(&main, (void *) 0);
		if(childsts == 0)
			exits(nil);
		else {
			fprint(2, "someinit failed\n");
			exits("some failed");
		}
	}
}
