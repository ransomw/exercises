#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAXLINE	10

int getline(char line[], int maxline);
void copy(char to[], char from[]);

void
main(void)
{
	int len;
	int max_len;
	char line[MAXLINE];
	char longest[MAXLINE];

	max_len = 0;
	while((len = getline(line, MAXLINE)) > 0)
		if(len > max_len) {
			copy(longest, line);
			max_len = len;
		}

	if(max_len > 0)
		printf("%d: %s", max_len, longest);

	exits(0);
}

// todo: style
int
getline(char s[], int lim)
{
	int c, i;

	for(i = 0; 
		i < lim-2 && 
			(c=getchar())!=EOF && 
			c != '\n'; 
		++i)
		s[i] = c;

	s[i] = '\n';
	s[i+1] = '\0';

	if(c != '\n' && c != EOF)
		while((c=getchar())!=EOF && c != '\n')
			++i;
	if(c == '\n')
		++i;
	
	return i;
}

/**
 * copy `from` into `to`, assuming enough space is allocated for `to`
 */
void
copy(char to[], char from[])
{
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}
