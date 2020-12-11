#include <u.h>
#include <libc.h>

void
main(void)
{
	print("running ls\n");
	/* exec() and execl() replace the current process
	 * with the supplied program and given arguments.
	 *
	 * that is, all memory segments are replaced
	 * by those of the new program.
	 */
	execl("/bin/ls", "ls", "-l", "/usr", nil);
	print("exec failed: %r\n");
}
