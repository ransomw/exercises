#include <u.h>
#include <libc.h>
#include <stdio.h>

/* that process data structure in the kernel
 * has access to environment variables via getenv()
 */

void
main(void)
{
	print("'%s' '%s' '%s'\n",
		getenv("home"),
		getenv("path"), /* a single string here */
		getenv("myenvvar"));

	putenv("mycenvvar", "stuff");

	exits(0);
}
