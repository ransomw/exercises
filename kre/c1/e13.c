#include <u.h>
#include <libc.h>
#include <stdio.h>

/* ignore words greater length than this less one */
#define MAX_COUNT	8

void
main(void)
{
	int c, i, j, ncurr;
	int nchars[MAX_COUNT + 1];
	/* for histogram */
	int nchars_max;

	ncurr = 0;
	for(i = 0; i < MAX_COUNT; ++i)
		nchars[i] = 0;

	while((c = getchar()) != EOF)
		if(c == ' ' || c == '\n' || c == '\t') {
			if(ncurr < MAX_COUNT)
				++nchars[ncurr];
			ncurr = 0;
		} else
			++ncurr;
	if(ncurr < MAX_COUNT)
		++nchars[ncurr];

	/* vertical histogram */

	nchars_max = 0;
	for(i = 0; i < MAX_COUNT; ++i)
		if(nchars[i] > nchars_max)
			nchars_max = nchars[i];

	for(j = nchars_max; j > 0 ; --j) {
		printf("%3d", j);
		for(i = 1; i < MAX_COUNT; ++i)
			if(nchars[i] >= j)
				printf("  #  ");
			else
				printf("     ");
		printf("\n");
	}
	printf("   ");
	for(i = 1; i < MAX_COUNT; ++i)
		printf(" %3d ", i);
	printf("\n");

	exits(0);
}
