#include <u.h>
#include <libc.h>
#include <stdio.h>

/* todo: largest negative number concerns.
 *   also, this implementation smells funny
 */

void itoa(int n, char s[]);

void
main(void)
{
	char s[12];

	itoa(98765430, s);
	printf("%s\n", s);
	itoa(-98765430, s);
	printf("%s\n", s);

	exits(0);
}



int
ld(int n)
{
	return abs(n) % 10 + '0';
}

int
itoarecurse(int n, char s[], int k)
{
	int l;
	int rest = n / 10;
	if(rest == 0) {
		int i = 0;
		if(n < 0)
			s[i++] = '-';
		s[i++] = ld(n);
		s[k + 1] = '\0';
		return i;
	}
	l = itoarecurse(rest, s, k + 1);
	s[l] = ld(n);
	return l + 1;
}

void
itoa(int n, char s[])
{
	itoarecurse(n, s, 0);
}
