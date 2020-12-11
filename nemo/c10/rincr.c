#include <u.h>
#include <libc.h>

/* Fork is just a call of rfork(RFFDG|RFREND|RFPROC) */

/* rfork() forks various system resources (including processes)
 * in various ways.
 * the most significant for the sake of concurrent programming
 * is the RFMEM flag, which specifies that the newly created
 * process shares memory with its parent -- i.e. the child
 * process gets access to the same BSS segment or what's
 * labelled [uninitialized data] in c2/loaded_programs.rc
 *
 * in particular, global variables are in the BSS segment
 * and shared between processes, while function-local variables
 * are on the stack segment, and not shared.
 */

int cnt, locout;

void
main(void)
{
	int i, loc;

	if(rfork(RFPROC|RFMEM
		/* this flag prevents the parent process
		 * from being able to get wait() data from
		 * the child. (cf. c4/runsync.c)
		 *
		 * commenting it out has no effect on the output
		 * of this program.
		 */
			|RFNOWAIT
			) < 0)
		sysfatal("fork: %r");


	/* soo this increments the integer stored at
	 * one memory address twice...
	 */
	cnt++;
	/* and remember that io is waaay slower than compute,
	 * so while one process is printing '1', the other has
	 * already incremented `cnt` and will print '2'.
	 *
	 * sometimes these prints occur in the opposite order.
	 */
	print("cnt is %d\n", cnt);

	/* usually, this increments twice, because
	 * locout is in the BSS segment.
	 */
	locout = cnt;
	sleep(1);
	locout++;
	cnt = locout;

	print("cnt is %d\n", cnt);


	/* this almost always increments `cnt` once,
	 * because loc is in the stack segment and
	 * different for each process.
	 */
	loc = cnt;
	sleep(1);
	/* so each process increments loc separateley */
	loc++;
	/* and writes the same result to cnt twice,
	 * thus incrementing cnt once
	 */
	cnt = loc;

	print("cnt is %d\n", cnt);

	exits(nil);
}
