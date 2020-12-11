#include <u.h>
#include <libc.h>

/*
 * Fork is just a call of rfork(RFFDG|RFREND|RFPROC).
 *
 * the r is for resource, and resources comprise all sorts of
 * operating system primitives
 * - memory
 * - file descriptors
 * - environment variables
 * - namespaces
 * - note and rendezvous groups
 *
 * by default, rfork() copies memory and shares other resources with
 * the parent process.
 */

void
main(void)
{

	switch(rfork(
		/* RFork File Descriptor Group
		 * creates a copy of the file descriptor table
		 * mapping integers to Chans.  it's also possible
		 * to share the same table or to create a new one.
		 *
		 * RFCFDG provides a Clean
		 * file descriptor table.  the C prefix can similarly
		 * provide fresh resources for all the system
		 * primitives listed above.
		 *
		 * with a Clean file descriptor table, there is
		 * no stdout to print to
		 */
			RFCFDG|
		/* RFork Rendezvous group */
			RFREND|
		/* RFPROC is the flag that specifies a 'fork'
		 * in the sense of control flow, the most obvious
		 * feature of fork() in c4/
		 *
		 * without RFPROC present, rfork() modifies the current
		 * process.
		 */
			RFPROC
			)) {
	case -1:
		sysfatal("fork failed");
	case 0:
		execl("/bin/ls", "ls", nil);
		break;
	default:
		/* same as wait() except returns process id only
		 * instead of WaitMsg struct
		 */
		waitpid();
		break;
	}
	exits(nil);
}
