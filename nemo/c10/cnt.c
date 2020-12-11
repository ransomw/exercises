#include <u.h>
#include <libc.h>

/* this is a toy example to demonstrate a rfork()
 * as in lock.c, except with two flows of control.
 *
 * the take-home is that while each process can use lock()
 * to ensure it's the only process that has access to `cnt`
 * at a given time, there's no way to coordinate lock
 * acquisition.
 *
 * instead of two processes with a single flow of control
 * competing for shared memory as in rincr.c, here we have
 * two processes with different control flows competing for
 * lock acquisition (although it is gauranteed that at most
 * one process will update `cnt` at a time).
 */

int cnt;
Lock cntlck;

void
main(void)
{
	long last, now;
	switch(rfork(RFPROC|RFMEM|RFNOWAIT)) {
	case -1:
		sysfatal("fork: %r");
	case 0:
		last = time(nil);
		for(;;) {
			lock(&cntlck);
			assert(cnt >= 0);
			cnt++;
			unlock(&cntlck);
			now = time(nil);
			if(now - last >= 2) {
				lock(&cntlck);
				print("cnt=%d\n", cnt);
				unlock(&cntlck);
				last = now;
			}
		}
	default:
		for(;;) {
			lock(&cntlck);
			assert(cnt >= 0);
			if(cnt > 0)
				cnt--;
			unlock(&cntlck);
		}
	}
}
