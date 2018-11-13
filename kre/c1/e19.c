#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAXLINE	1000 /* maximum input line length */

int getline(char line[], int maxline);
void reverse(char s[], int len);

void
main(void)
{
	int len;
	char line[MAXLINE];

	while((len = getline(line, MAXLINE)) > 0) {
		if(line[len-1] == '\n')
			reverse(line, len-2);
		else
			reverse(line, len-1);
		printf("%s", line);
	}

	exits(0);
}

int
getline(char s[], int lim)
{
	int c, i;

	for(i = 0; 
		i < lim-1 && 
			(c=getchar())!=EOF && 
			c != '\n'; 
		++i)
		s[i] = c;
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/**
 * reverse in place s.t. s[0], s[1], ..., s[len-1], s[len]
 * becomes s[len], s[len-1], ..., s[1], s[0]
 */
void
reverse(char s[], int len)
{
	int i, j, c;

	for(i = 0; i < len/2; ++i) {
		c = s[i];
		j = len - i;
		s[i] = s[j];
		s[j] = c;
	}
}
