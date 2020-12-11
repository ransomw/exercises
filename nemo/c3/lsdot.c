#include <u.h>
#include <libc.h>

/* dirread() wraps read() with functionality to unpack
 * data from read() into Dir structs as in stat.c
 */

void
main(void)
{
	Dir *dents;
	int ndents, fd, i;

	fd = open(".", OREAD);
	if(fd < 0)
		sysfatal("open: %r");

	/* note that dirread() is not gauranteed to return
	 * all directory entries at once, hence this outer
	 * loop.
	 */
	while((ndents = dirread(fd, &dents)) != 0) {
	//	print("*\t%d\n", ndents);
		for(i = 0; i < ndents; i++)
			print("%s\n", dents[i].name);
		free(dents);
	}
	exits(nil);
}
