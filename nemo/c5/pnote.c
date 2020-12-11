#include <u.h>
#include <libc.h>

/* notes are kind of like signals on *nix, except,
 * like the difference return values and exit statuses,
 * they're strings instead of integers.
 *
 * to send a note to this program, find its pid from `ps` and
 *
 * term% echo 'whatev note text' > /proc/<pid>/note
 *	# don't begin with 'suicide:',  b/c that's reserved
 *	# for the kernel when programs attempt to divide by
 *	# zero, etc.
 *
 * then, whenever the kernel executes again (meaning this, the
 * process receiving the note, is in a syscall), the handler
 * is called.
 *
 * if the process receiving the note is in a blocking syscall
 * io, sleep, etc., then the syscall is interrupted
 * (i.e. syscall returns -1, "%r" == "interrupted").
 * otherwise, the syscall is allowed to complete.
 *
 * in either case, control flow jumps from the syscall
 * (or function making the syscall) to the handler functions
 * registered with
	athandler(<handler_fn_ptr>, 1);
 * handler functions can be unregistered, too, with 
	athandler(<handler_fn_ptr>, 0);
 *
 * handler functions are then run in the order they've been
 * registered until
 * 1. one of them returns a true (!= 0) value
 *	or
 * 2. all handler functions have been run.
 *
 * if (1), the process continues from the syscall that was
 * occurring when the note was posted, and in case of (2),
 * the process is killed off by the kernel.
 */

/* first param is process registers at time of note,
 * seldom used.  msg is text from kernel
 */
int handler(void *, char *msg)
{
	print("note: %s\n", msg);
	return 0;
}

int handlerdos(void *, char *msg)
{
	print("note again: %s\n", msg);
	return 1;
}

void
main(void)
{
	char c;

	atnotify(handler, 1);
	atnotify(handlerdos, 1);

	read(0, &c, 1);

	print("done (%r)\n");

	exits(nil);
}
