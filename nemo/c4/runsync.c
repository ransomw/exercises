#include <u.h>
#include <libc.h>

int
run(char *cmd, char *argv[])
{
	Waitmsg *m;
	int ret;
	int pid;

	pid = fork();
	switch(pid) {
	case -1:
		return -1;
	case 0:
		exec(cmd, argv);
		sysfatal("exec: %r");
	default:
		/* wait() is the new piece of the puzzle here.
		 *
		 * await() is the corresponding system call,
		 * with wait() providing some parsing
		 * to convert raw chars into a Waitmsg.
		 */
		while(m = wait()) {
			/* since wait() returns when *any*
			 * child process exits, it's necessary
			 * to check the Waitmsg and see if
			 * the process corresponding to the
			 * pid above is the one that's just
			 * exited
			 */
			if(m->pid == pid) {
				if(m->msg[0] == 0)
					ret = 0;
				else {
					werrstr(m->msg);
					ret = -1;
				}
				free(m);
				return ret;
			}
			free(m);
		}
	}
	return -1;
}

void
main(void)
{
	char *margv[] = {"ls", "-l", "/usr", nil};
	char *sargv[] = {"sig", "print", nil};

	print("running ls\n");
	run("/bin/ls", margv);
	print("ran ls\n");

	/* note that files starting with a shebang
	 * are executed by the system, not the shell,
	 * as interpreted files
	 */
	print("running sig\n");
	run("/bin/sig", sargv);
	print("ran sig\n");

}
