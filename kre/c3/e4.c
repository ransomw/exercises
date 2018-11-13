#include <u.h>
#include <libc.h>
#include <stdio.h>

void reverse(char s[]);
void itoa(int n, char s[]);

void
main(void)
{
	char a[100];

	itoa(123, a);
	printf("%s\n", a);
	itoa(-123, a);
	printf("%s\n", a);
	itoa(-120, a);
	printf("%s\n", a);
	itoa(2147483647, a);
	printf("%s\n", a);
	itoa(-2147483647, a);
	printf("%s\n", a);
	itoa(-2147483648, a);
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
itoa(int n, char s[])
{
	int i, sign;
	/* the unary - operator of the largest negative
	 * integer value in two's compliemnt notation
	 * is always the value itself.  that's because
	 * in two's compliment notation, the largest
	 * negative value is distance 1 more than
	 * the largest postive value from zero.
	 * as a workaround, use the additional observation that
	 * and the largest negative value is a power of 2.
	 */
	if((sign = n) < 0)
		if(!(sign % 2) && sign % 5)
			n = -(n + 1);
		else
			n = -n;
	i = 0;
	do {
		s[i++] = (n % 10) + '0';
	} while((n /= 10) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	if(sign < 0 && !(sign % 2) && sign % 5)
		s[i-1]++;
}
