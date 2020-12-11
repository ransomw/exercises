#include <u.h>
#include <libc.h>

/* sequel to pipeto.c *

/* assume buf is enough to contain cmd's output */
long
cmdoutput(char *cmd, char *buf, long len)
{
	int fd[2];
	long nr, tot;

	if(pipe(fd) < 0)
		return -1;
	switch(fork()) {
	case -1:
		return -1;
	case 0:
		close(fd[0]);
		dup(fd[1], 1);
		close(fd[1]);
		execl("/bin/rc", "rc", "-c", cmd, nil);
		sysfatal("exec");
	default:
		close(fd[1]);
		for(tot = 0; len - tot > 1; tot += nr) {
			nr = read(fd[0], buf + tot, len - tot);
			if(nr <= 0)
				break;
		}
		close(fd[0]);
		/* wait on child *after* reading everything
		 * (by assumption about buffer size) from
		 * the pipe.
		 *
		 * waiting before reading when there's more
		 * data than will fit in the pipe causes
		 * /deadlock/ -- i.e. the parent waits
		 * on the child to finish, and the child
		 * never finishes because writes to full
		 * pipes are blocking.
		 */
		waitpid();
		buf[tot] = '\0';
		return tot;
	}
}

void
main(void)
{
	char buf[1024];

	cmdoutput("grep main *.c", buf, sizeof buf);

	print("***\n%s\n***\n", buf);

	exits(nil);
}
