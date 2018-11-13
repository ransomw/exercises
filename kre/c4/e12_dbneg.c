#include <u.h>
#include <libc.h>
#include <stdio.h>

/*

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
ch(int n, char s[], int k)
{
	int l;
	int rest = n / 10;
	if(rest == 0) {
		int i = 0;
		s[i++] = n % 10 + '0';
		s[k + 1] = '\0';
		return i;
	}
	l = ch(rest, s, k + 1);
	s[l] = n % 10 + '0';
	return l + 1;
}

void
itoa(int n, char s[])
{
	ch(n, s, 0);
}
