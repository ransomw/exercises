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

	ncurr = 0;
	for(i = 0; i < MAX_COUNT; ++i)
		nchars[i] = 0;

	// todo: dedupe nchars inc.  recall, functions not yet covered.
	while((c = getchar()) != EOF)
		if(c == ' ' || c == '\n' || c == '\t') {
			if(ncurr < MAX_COUNT)
				++nchars[ncurr];
			ncurr = 0;
		} else
			++ncurr;
	if(ncurr < MAX_COUNT)
		++nchars[ncurr];

	/* NB. print() and printf() use different buffers.
	 *     using print() instead of printf() will cause unexpected
	 *     results */
	for(i = 1; i < MAX_COUNT; ++i) {
		printf("%3d : ", i);
		for(j = 0; j < nchars[i]; ++j)
			printf("#");
		printf("\n");
	}

	exits(0);
}
