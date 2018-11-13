#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * count spaces, tabs, newlines
 */
void
main(void)
{
	int c, nl, nt, ns;

	nl = 0; ns = 0; nt = 0; 
	while((c = getchar()) != EOF) {
		if(c == '\n') ++nl;
		if(c == ' ') ++ns;
		if(c == '\t') ++nt;
	}

	printf("lines : %d\n", nl);
	printf("tabs: %d\n", nt);
	printf("spaces: %d\n", ns);

	exits(0);
}
