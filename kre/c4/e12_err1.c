#include <u.h>
#include <libc.h>
#include <stdio.h>

/*
	if(n < 0) {
		s[k++] = '-';
		n = -n;
	}
*/

void itoa(int n, char s[]);

void
main(void)
{
	char s[10];
	
	itoa(9876, s);
	printf("%s\n", s);
	printf("%c %c %c %c\n", 'x', s[1], s[2], s[3]);
	
	exits(0);
}

int
itoa_h(int n, int d, char s[], int k)
{
	int rest;
	int l;

	if(n)
		l = itoa_h(n / 10, s, k + 1);
	else {
		printf("**\t%d\n", k);
		s[k + 1] = '\0';
		return k;
	}
	printf("*\t%c %d %c\n", l, k, d + '0');
	return d + '0';
}

void itoa(int n, char s[])
{
	itoa_h(n, n % 10, s, 0);
}
