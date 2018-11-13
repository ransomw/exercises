#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAXLINE	1000 /* maximum input line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/**
 * print the longest line among several lines of input
```pseudo
while(there's another line)
	if(it's longer than the previous line)
		(save it)
		(save its length)
print longest line
```
 */
void
main(void)
{
	int len; // curr line
	int max; // thus far
	char line[MAXLINE]; // curr line
	char longest[MAXLINE]; // longest line thus far

	max = 0;
	while((len = getline(line, MAXLINE)) > 0)
		/* todo: ('til malloc) ignores len == MAXLINE */
		if(len > max) {
			max = len;
			copy(longest, line);
		}

	if(max > 0)
		printf("%s", longest);

	exits(0);
}

/**
 * read a line into s, return length or 0 if EOF
 */
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
	/* this is the 'null character', used by the C language
	 * to mark the end of string literals --- i.e. a literal
	 * "asdf" is an array of characters 'a' 's' 'd' 'f' '\0'.
	 *
	 * the standard library's %s (string) format spec to printf
	 * relies on the same convention:  strings end with a null
	 * character, as does the copy() function below. */
	s[i] = '\0';
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
