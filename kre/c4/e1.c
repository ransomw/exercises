#include <u.h>
#include <libc.h>
#include <stdio.h>

int strlindex(char s[], char t[], int i);
int strindex(char s[], char t[]);

void
main(void)
{

	printf("8 %d\n", strindex("asdfasdfqwer", "qwer"));
	printf("12 %d\n", strindex("asdfqwerasdfqwer", "qwer"));
	printf("-1 %d\n", strindex("asdfasdfqwer", "qwert"));
	printf("-1 %d\n", strindex("a", ""));
	printf("-1 %d\n", strindex("", "a"));

	exits(0);
}

/* leftmost index of t in s starting at i */
int
strlindex(char s[], char t[], int i)
{
	int j, k;

	for(; s[i] != '\0'; i++) {
		for(j=i, k=0;
			t[k] != '\0' && s[j] == t[k];
			j++, k++)
			;
		if(k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

/* rightmost index of t in s */
int
strindex(char s[], char t[])
{
	int i, index;

	i = index = -1;
	while((i = strlindex(s, t, index + 1)) != -1)
		index = i;
	return index;
}
