#include <u.h>
#include <libc.h>

/* this is a first demo of using pipes for interprocess
 * communication from C
 */

int
pipeto(char *cmd)
{
	int fd[2];

	/* pipes for interprocess communication must be
	 * created *before* the fork() to create processes
	 * in order for each process to get an end of the same
	 * pipe
	 */
	pipe(fd);
	switch(fork()) {
	case -1:
		return -1;
	case 0:
		/* closing unused ends of the pipe after the
		 * fork helps prevent programming errors
		 */
		close(fd[1]);
		dup(fd[0], 0);
		/* in fact, closing unused file-descriptors
		 * asap is good practice
		 */
		close(fd[0]);
		/* so when cmd runs, its stdin is connected
		 * to fd[0], the read end of the pipe
		 */
		execl("/bin/rc", "rc", "-c", cmd, nil);
		sysfatal("execl");
	default:
		close(fd[0]);
		return fd[1];
	}
}

void
main(void)
{
	int fd, i;
	char *msgs[] = {
		"warning: the world is over\n",
		"span: earn money real fast!\n",
		"warning: it was not true\n"};

	fd = pipeto("grep warning");
	if(fd < 0)
		sysfatal("pipeto: %r");
	for(i = 0; i < nelem(msgs); i++)
		write(fd, msgs[i], strlen(msgs[i]));
	close(fd);
	/* when this process exits, the child process
	 * is still running, processing data on the pipe
	 */

	exits(nil);
}
