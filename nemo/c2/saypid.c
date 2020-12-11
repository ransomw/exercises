#include <u.h>
#include <libc.h>

void
main(void)
{
	int pid;

	pid = getpid();
	print("pid of this process is %d\n", pid);
	exits(nil);
}
