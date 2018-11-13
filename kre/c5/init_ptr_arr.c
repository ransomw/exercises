#include <u.h>
#include <libc.h>
#include <stdio.h>

char *month_name(int n);

void
main(void)
{
	int i;

	for(i = 0; i < 14; i++) {
		printf("%s\t\t", month_name(i));
		if(i % 4 == 0)
			printf("\n");
	}
	printf("\n");
	exits(0);
}


char
*month_name(int n)
{
	/* same type as lineptr in sort.c */
	static char *name[] = {
		"Illegal month",
		"Jan", "Feb", "Mar", "Apr",
		"May", "June", "July", "Aug",
		"Sept", "Oct", "Nov", "Dec"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];	
}
