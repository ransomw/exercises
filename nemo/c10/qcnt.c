#include <u.h>
#include <libc.h>

/* motivated by cnt.c, this program introduces Q for Queue[ing]
 * locks.  these locks are queued in the sense of calls to
 * qlock() being first-call-first-acquire.
 * 
 * so this program increments and decrements cnt by turns,
 * while cnt.c provides no gaurantees about which of the
 * inc and dec critical sections has access to the lock.
 *
 * the mechanism for implementing the locks' queue is rendezvous,
 * the topic of the next section of the text.
 */

int cnt;
QLock cntlck;

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
			qlock(&cntlck);
			assert(cnt >= 0);
			cnt++;
			print("cnt=%d\n", cnt);
			qunlock(&cntlck);
		}
	default:
		for(;;) {
			qlock(&cntlck);
			assert(cnt >= 0);
			if(cnt > 0)
				cnt--;
			print("cnt=%d\n", cnt);
			qunlock(&cntlck);
		}
	}
}
