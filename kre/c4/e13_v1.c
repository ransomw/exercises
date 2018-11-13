#include <u.h>
#include <libc.h>
#include <stdio.h>

void reverse(char[]);

void
main(void)
{
	char s[] = "asdfqwerty";

	reverse(s);
	printf("%s\n", s);
	
	exits(0);
}

void
swap(char s[], int i, int j)
{
	int temp;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

rh(char s[], int k)
{
	int l;
	if(s[k] == '\0') {
		return 0;
	}
	l = rh(s, k + 1);
	/* todo:  this conditional is more stank.
	 *   terrible, terrible computer programming
	 */
	if(l < k)
		swap(s, l, k);
	return l + 1;
}

void
reverse(char s[])
{
	rh(s, 0);
}
