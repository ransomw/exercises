#include <u.h>
#include <libc.h>

/* the RFNOWAIT flag, when used with the RFPROC flag,
 * causes the child process not to leave an exit message.
 * use RFNOWAIT whenever the parent will not use the await()
 * syscall (e.g. via wait() or waitpid()) to coordinate
 * the child process's exit.
 *
 * doing otherwise will result in the child process's
 * exit information (pid, times, exit string) lingering around
 * in the kernel, unused.
 *
 * compare this program with c4/intfork.c, where the
 * standard RFFDG|RFREND|RFPROC flags were used because
 * rfork() had not been revealed as the mechanism for fork()
 */


void
main(void)
{
	switch(rfork(RFFDG|RFREND|RFPROC | RFNOWAIT)) {
	case -1:
		sysfatal("fork failed");
	case 0:
		print("child\n");
		break;
	default:
		print("parent\n");
		break;
	}
	exits(nil);
}
