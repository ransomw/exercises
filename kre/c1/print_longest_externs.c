#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAXLINE	1000 /* maximum input line length */

/* external variables --- i.e. variables that can be accessed by name
 * by any function --- can be used instead of argument lists to
 * communicate data between functions..
 *
 * the following *defines* three external variables,
 * setting aside storage.  external variables are *defined*
 * exactly once each. */
int max; // thus far
char line[MAXLINE]; // curr line
char longest[MAXLINE]; // longest line thus far

/* the `(void)` parameter list explicitly declares no parameters.
 * using a `()` parameter list instead indicates no parameter
 * checks on function prototypes. */
int getline(void);
void copy(void);

/**
 * see print_longest.c -- this version is "worse" and only
 * exists to demonstrate external variables.
 */
void
main(void)
{
	int len;
	/* the `extern` token *declares* external variables used
	 * in a function.  *declarations* may be explicit (`extern`)
	 * or implicit:  when the definition occurs in the same
	 * source file, declarations (such as these) are redundant. */
	extern int max;
	extern char longest[];

	max = 0;
	while((len = getline()) > 0)
		if(len > max) {
			max = len;
			copy();
		}

	if(max > 0)
		printf("%s", longest);

	exits(0);
}

int
getline(void)
{
	int c, i;
	extern char line[];

	for(i = 0; 
		i < MAXLINE-1 && 
			(c=getchar())!=EOF && 
			c != '\n'; 
		++i)
		line[i] = c;
	if(c == '\n') {
		line[i] = c;
		++i;
	}

	line[i] = '\0';
	return i;
}

void
copy(void)
{
	int i;
	extern char line[], longest[];

	i = 0;
	while((longest[i] = line[i]) != '\0')
		++i;
}
