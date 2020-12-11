#include <u.h>
#include <libc.h>

/* when one program wants to run another program,
 * it proceeds by two steps (system calls)
 *
 * 1. create a new process to run the other program in
 * 2. run the program in that process
 *
 * separating process creation from program invocation
 * allows arbitrary customization of the process
 * before invoking the other program
 */

void
main(void)
{
	/* fork() creates a new (child) process.
	 * the program that calls fork() continues executing
	 * in both the child process and the original (parent)
	 * process.
	 */
	switch(fork()) {
	case -1:
		sysfatal("fork failed");
	/* in the child process, fork() returns 0 */
	case 0:
		/* start /bin/ls program with argv = {"ls"} */
		execl("/bin/ls", "ls", nil);
		break;
	/* in the parent process, fork() returns the
	 * child process's process id
	 */
	default:
		print("ls started\n");
	}
	exits(nil);
}
