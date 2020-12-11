#include <u.h>
#include <libc.h>
#include <thread.h>

/* here's a further variation on c10/cnt.c and c10/qcnt.c ..
 * notice the use of yield() to cede control of one thread to the other.
 *
 * try running acid on this program with `-l thread`
 * such that the threads() and stacks() functions are available to acid
 * todo: 
	/sys/lib/acid/thread:1: (error) pushfile: /sys/src/libthread/sched.386.acid: '/sys/src/libthread/sched.386.acid' does not exist
 * when passing `-l thread` to acid
 */

int cnt;

void
incr(void *arg)
{
	int *cp = arg;

	threadsetname("incrthread");
	for(;;) {
		*cp = *cp + 1;
		print("cnt %d\n", *cp);
		/* try commenting out this yield() */
		yield();
	}
	threadexits(nil);
}

void
decr(void *arg)
{
	int *cp = arg;

	threadsetname("decrthread");
	for(;;) {
		*cp = *cp - 1;
		print("cnt %d\n", *cp);
		yield();
	}
	threadexits(nil);
}

void
threadmain(int, char *[])
{
	threadsetname("main");
	threadcreate(incr, &cnt, 8*1024);
	threadcreate(decr, &cnt, 8*1024);
	threadexits(nil);
}
