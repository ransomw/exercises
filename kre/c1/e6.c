#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	print("press enter or ^D\n");
	printf("%d\n", getchar() != EOF);

	exits(0);
}
