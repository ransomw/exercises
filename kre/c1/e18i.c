#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAXLINE	1000 /* maximum input line length */

int getline(char line[], int maxline);

/**
```pseudo	 	  
while(there's another line)
	(read the line)   
	(set the null character after the last non-blank character)
	if(the null character is not the first character)
		(print the edited line followed by a newline)	
```
*/
void
main(void)
{
	int len;
	char line[MAXLINE];

	while((len = getline(line, MAXLINE)) > 0) {
		for(--len; len >= 0 &&
			(line[len] == '\n' ||
				line[len] == ' ' ||
				line[len] == '\t');
			--len)
			;
		if(len >= 0) {
			line[len+1] = '\0';
			printf("%s\n", line);
		}
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
