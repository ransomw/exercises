#include <u.h>
#include <libc.h>
#include <stdio.h>

#define NUM_DIGITS	10
#define NUM_ALPHA	('z'-'a')

void
main(void)
{
	int c, i, j, nwhite, nother;
	/* array of ten integers, ndigit[0] .. ndigit[9] */
	int ndigit[NUM_DIGITS];
	int nalpha[NUM_ALPHA];

	nwhite = nother = 0;
	for(i = 0; i < NUM_DIGITS; ++i)
		ndigit[i] = 0;

	for(i = 0; i < NUM_ALPHA; ++i)
		nalpha[i] = 0;


	while((c = getchar()) != EOF)
		/* '0' .. '9' have inc int vals in all charsets */
		if(c >= '0' && c <= '9')
			/* 0 <= c-'0' <= 9 */
			++ndigit[c-'0'];
		else if(c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else if(c >= 'a' && c <= 'z')
			++nalpha[c-'a'];
		else if(c >= 'A' && c <= 'Z')
			++nalpha[c-'A'];
		else
			++nother;


	for(i = 0; i < NUM_DIGITS; ++i) {
		printf("%1d : ", i);
		for(j = 0; j < ndigit[i]; ++j)
			printf("#");
		printf("\n");
	}
	for(i = 0; i < NUM_ALPHA; ++i) {
		printf("%c : ", 'A' + i);
		for(j = 0; j < nalpha[i]; ++j)
			printf("#");
		printf("\n");
	}



	exits(0);
}
