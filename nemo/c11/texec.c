#include <u.h>
#include <libc.h>
#include <thread.h>

/* the plan 9 C api is designed, as a whole, to be used with libthread,
 * so the 'thread safe' distinction from *nix environments isn't as
 * meaningful.  there are, however, a few functions that aren't designed
 * to be used with threads, such as exec() and wait().  this program
 * demonstrates the libthread substitutes, procexec() and
 * threadwaitchan().  a similar exception is using threadnotify()
 * instead of atnotify() to handle notes.
 *
 * recall that exec() and similar expect an absolute path to an
 * executable, such as /bin/date instead of just date.
 */

Channel *waitc;
Channel *pidc;

void
cmdproc(void *arg)
{
	char *cmd = arg;

	procexecl(pidc, cmd, cmd, nil);
	sysfatal("procexecl: %r");
}

void
threadmain(int, char *[])
{
	char ln[512];
	int pid, nr;
	Waitmsg *m;

	write(1, "cmd? ", 5);
	nr = read(0, ln, sizeof(ln) - 1);
	if(nr <= 1)
		threadexits(nil);
	ln[nr-1] = '\0'; /* omit newline char */
	pidc = chancreate(sizeof(ulong), 1);
	waitc = threadwaitchan();
	proccreate(cmdproc, ln, 8*1024);
	pid = recvul(pidc);
	print("started new proc pid=%d\n", pid);
	if(pid >= 0) {
		m = recvp(waitc);
		print("terminated pid=%d status=%s\n",
			m->pid, m->msg);
		free(m);
	}
	threadexits(nil);
}
