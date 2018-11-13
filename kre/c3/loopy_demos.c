#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);
void reverse(char s[]);
void itoa(int n, char s[]);

void
main(void)
{
	char s[] = "asdf";
	char a[100];
	reverse(s);
	itoa(-123, a);
	printf("%d\n", atoi("-321"));
	printf("%s\n", s);
	printf("%s\n", a);
	itoa(-2147483647, a);
	printf("%s\n", a);
	itoa(-2147483648, a);
	printf("%s\n", a);

	int x = -2147483647;
	int y = -x;
	int z = x % 10;
	printf("%d %d %d\n", x, y, z);
	x = -2147483648;
	y = -x;
	z = x % 10;
	printf("%d %d %d\n", x, y, z);
}

/*
 * while and for
 */


/* atoi: convert string to integer */
int
atoi(char s[])
{
	int i, n, sign;

	/* skip white space, if any */
	for(i = 0; isspace(s[i]); i++)
		;
	/* get sign, if any */
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	/* see also: c2/type_conversions.c */
	for(n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}

/* shellsort: short v[0]...n[n-1] into increasing order
 *	invented in 1959 by D.L. Shell
 */
// todo: verify correctness
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	/* the gap between compared elements shrinks each pass */
	for(gap = n/2; gap > 0; gap /= 2)
		/* step along each element */
		for(i = gap; i < n; i++)
			for(j = i - gap;
				j >= 0 && v[j] > v[j+gap];
				j -= gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
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

	if((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = (n % 10) + '0';
	} while((n /= 10) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
