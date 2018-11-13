#include <u.h>
#include <libc.h>
#include <stdio.h>

void reverse(char s[]);
void itob(int n, char s[], int b);

void
main(void)
{
	char a[100];
	itob(0xAA, a, 16);
	printf("%s\n", a);
	itob(-0xAA, a, 16);
	printf("%s\n", a);
	itob(077, a, 8);
	printf("%s\n", a);

	itob(123, a, 10);
	printf("%s\n", a);
	itob(-123, a, 10);
	printf("%s\n", a);
	itob(-120, a, 10);
	printf("%s\n", a);
	itob(2147483647, a, 10);
	printf("%s\n", a);
	itob(-2147483647, a, 10);
	printf("%s\n", a);
	itob(-2147483648, a, 10);
	printf("%s\n", a);
}

/* reverse a string in place */
void
reverse(char s[])
{
	int c, i, j;

	for(i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa: convert n to characters in s */
void
itob(int n, char s[], int b)
{
	int i, sign, rem;

	if((sign = n) < 0)
		if(!(sign % 2) && sign % 5)
			n = -(n + 1);
		else
			n = -n;
	i = 0;
	do {
		s[i++] = (rem = n % b) > 9 ? 
				(rem - 10) + 'A' : 
				rem + '0';
	} while((n /= b) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	if(sign < 0 && !(sign % 2) && sign % 5)
		s[i-1]++;
}
