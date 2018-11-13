#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	// \a is the alert bell
	printf("\ahello world\a\n"
	// Plan 9 unicode support
	printf("ミドリ\n");
	// todo: try out all the escape codes in 2.3 (p. 37)
	exits(0);
}
