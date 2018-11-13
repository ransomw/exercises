#include <u.h>
#include <libc.h>
#include <stdio.h>

int
getline(char s[], int lim)
{
	int c = EOF, i;

	i = 0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
