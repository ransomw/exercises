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
lrot(char s[], int k)
{
	char c, first = s[k];
	int i;

	if(first == '\0')
		exits("attempting to rotate empty string");
	for(i = k; c = s[i + 1]; i++)
		s[i] = c;
	s[i] = first;
}

void
rh(char s[], int k)
{
	int n = k + 1;

	if(s[n] != '\0')
		rh(s, n);
	lrot(s, k);
}

void
reverse(char s[])
{
	rh(s, 0);
}
