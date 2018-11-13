#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * character occurance counter
 * (digits, white space, others)
 */
void
main(void)
{
	int c, i, nwhite, nother;
	/* array of ten integers, ndigit[0] .. ndigit[9] */
	int ndigit[10];

	nwhite = nother = 0;
	for(i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while((c = getchar()) != EOF)
		/* '0' .. '9' have inc int vals in all charsets */
		if(c >= '0' && c <= '9')
			/* 0 <= c-'0' <= 9 */
			++ndigit[c-'0'];
		else if(c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;

	print("digits =");
	for(i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n",
		nwhite, nother);


	exits(0);
}
