
/* there's a function called readn() that will block until
 * n bytes are read (recall the syscall returns /at most/
 * the specified number of bytes) ...
 * .. even readn() might read less than n bytes in the
 * event of a note interrupting the process.
 *
 * this is an example of the type of trickery that's
 * necessary when handling notes.
 *
 * if a program /doesn't/ handle notes, a note interrupting
 * the process will end the process, so recovering syscalls
 * from notes isn't an issue.
 */

long rreadn(int fd, char *buf, long n)
{
	long nr, tot;
	char err[128];

	for(tot = 0; tot < n; tot += nr) {
		nr = read(fd, buf + tot, n - tot);
		if(nr == 0)
			break;
		if(nr < 0) {
			rerrstr(err, sizeof err);
			if(strcmp(err, "interrupted") == 0)
				nr = 0;
			else
				break;
		}
	}
	return tot;
}
