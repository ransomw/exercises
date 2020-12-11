#include <u.h>
#include <libc.h>
#include <thread.h>

/* this is a first example of plan 9's threading library.
 * compare it to c10/rincr.c:  just as the operating system allows
 * multiple flows of control in terms of processes, one process
 * can have multiple flows of control in terms of threads.
 */

int cnt;

/* every thread other than the main thread is started by a function
 * with a sig like this
 */
void incrthread(void *);

/* threaded programs supply a threadmain() instead of main()
 */
void
threadmain(int, char *[])
{
	int i;

	/* threadcreate() starts a new thread.  its sig is
	 * threadcreate(void (*fn)(void*), void *arg, uint stacksize)
	 * where arg is the param passed to fn upon creating the thread.
	 * the thread's stack lives in the same uninitialized data
	 * segment as function-local variables, and its size must be
	 * specified when the thread is created.
	 */
	threadcreate(incrthread, nil, 8*1024);
	print("thread created\n");
	for(i = 0; i < 2; i++) {
		cnt++;
		/* see below */
	//	yield();
	}
	print("cnt in main thread is %d\n", cnt);
	/* threads call threadexits() to terminate.  the threading
	 * library keeps track of a processes' running threads and
	 * exits the process when all threads have terminated.
	 * the process exits with the status of the last thread to call
	 * threadexits().
	 */
	print("main thread exiting\n");
	threadexits(nil);
}

/* unlike processes, which rely on the kernel for changing from one
 * flow of control for the other, threads coordinate using the thread
 * library.  a thread does not stop running unless it cedes to another
 * thread via threadexits() or yield().
 * yield() stops the current thread and allows another to start running,
 * if any are scheduled, and then continues the original thread when
 * that other thread cedes control.  yield() has no effect if there
 * are no other threads scheduled.
 */

void
incrthread(void *)
{
	int i;

	for(i = 0; i < 2; i++)
		cnt++;
	print("cnt in incr thread is %d\n", cnt);
	threadexits(nil);
}
