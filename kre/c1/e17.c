#include <u.h>
#include <libc.h>
#include <stdio.h>

/* print lines of length more than this */
#define MIN_LEN 44

int getline(char s[], int lim);


/**
```pseudo
while(there's another line)
	(read up to min length buffer)
	if(the buffer's full)
		(print the buffer)
		if(the buffer doesn't contain the entire line)
			(read and print the rest of the line)
		
```
*/
void
main(void)
{
	char c, len;
	char line_buf[MIN_LEN+1]; // add space for null character

	while((len = getline(line_buf, MIN_LEN+1)) > 0)
		if(len >= MIN_LEN) {
			printf("%s", line_buf);
			if(line_buf[len-1] != '\n') {
				while((c=getchar())!=EOF && c != '\n')
					printf("%c", c);
				printf("\n");
			}
		}

	exits(0);
}

/**
 * read a line into s, return length or 0 if EOF.
 * lim is the space allocated for s, the maximum readable length
 * less one (for null chararacter).
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
	s[i] = '\0';
	return i;
}
