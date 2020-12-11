#include <u.h>
#include <libc.h>

/* processes can send notes to themselves via alarm().
 * every process has an alarm timer.
 */

int
handler(void *, char *msg)
{
	if(!strcmp(msg, "alarm")) {
		fprint(2, "timed out\n");
		return 1;
	}
	return 0;
}

void
main(void)
{
	char buf[1024];
	long nr;

	atnotify(handler, 1);
	print("type away!");

	/* set the alarm timer at 3 seconds and do a syscall */
	alarm(3 * 1000);
	nr = read(0, buf, sizeof buf);

	/* control can return here in two cases:
	 * (1) syscall returns or (2) alarm note is posted.
	 *
	 * in case of (1), turn off the alarm timer
	 * so futher syscalls aren't interrupted by the alarm
	 * note.
	 *
	 * alarm() use is inherently error-prone: since
	 * the time between a syscall and another call to
	 * alarm() is always non-negligable, it's always
	 * possible this
	 * 'set timer' -> 'syscall' -> 'zero timer'
	 * pattern will fail due to the timer expiring
	 * 'syscall' -----[here]-----> 'zero timer'
	 * if this occurs, the next syscall will get
	 * the "alarm" note.
	 */
	alarm(0);
	if(nr >= 0)
		write(1, buf, nr);

	exits(nil);
}
