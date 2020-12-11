#include <u.h>
#include <libc.h>

/* this follows up on the motivating example in rincr.c
 * to introduce lock() and unlock().
 *
 * Lock is a struct { int val; } defined in /sys/include/libc.h,
 * and unlock() sets lck->val = 0;
 *
 * lock(), otoh, is more difficult to understand because it
 * relies a on a small amount of assembly in /sys/src/libc/'*'/tas.s
 * to implement _tas(), aka test-and-set.
 * _tas(int *x) is an atomic (i.e. all at once) operation
 * to the effect of
if(&x == 0) {
	&x = 1; // or some non-zero value
	return 0;
} else
	return &x
 * there are various machine-dependent tricks in order to ensure
 * that process switching doesn't interfere with the shared
 * memory in x.
 */

int cnt;
Lock lck;

void
main(void)
{
	int loc;

	if(rfork(RFPROC|RFMEM|RFNOWAIT) < 0)
		sysfatal("fork: %r");

	lock(&lck);
	/* here, we say the lock has been acquired,
	 * because it has a nonzero value.
	 * one process can have the lock at a time.
	 */
	print("lock val %x\n", lck.val);
	loc = cnt;
	sleep(1);
	loc++;
	cnt = loc;
	unlock(&lck);

	print("cnt is %d\n", cnt);

	exits(nil);
}
