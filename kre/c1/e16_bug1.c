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

	int i = 0;
	
	max_len = 0;

	while(
		// (len = ++i)
		(len = getline(line, MAXLINE)) 
			> 0
			// < 4
		) {

		printf("curr max_len: %d, len: %d\n", max_len, len);

		if(len > max_len) {

			// printf("%d > %d: %s", len, max_len, line);

			// copy(longest, line);

			max_len = len;

		}

		printf("new max_len: %d, len: %d\n", max_len, len);


	}

/*
	if(max_len > 0)
		printf("%d: %s", max_len, longest);
*/

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
	
/* BUG -- s[i+1] = '\0' zeros out max_len on 8
	s[i] = '\n';
	s[i+1] = '\0';
*/

	s[i] = '\0';

	if(c == '\n')
		++i;
	else if(i >= lim-1 && c != EOF)
		while((c=getchar())!=EOF && c != '\n')
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
