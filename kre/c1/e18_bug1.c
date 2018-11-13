#include <u.h>
#include <libc.h>
#include <stdio.h>

/* experimenting with streaming buffer strategies.
 *  this one doesn't distinguish between trailing blanks
 *  and lines with only blanks.   consider that input
'asdf    
			qwer
			
			qwer    asdf   '
 * produces output
'asdf
		qwer

		qwer   asdf'
 * with an extra blank line.
 * i.e. this program removes trailing whitespace
 *   (buggy, note missing tab stop)
 *   but doesn't remove lines with blanks.
 */


#define BUF_SIZE	1000

int fill_buf(char s[], int lim);

void
main(void)
{
	int len;
	char buf[BUF_SIZE];

	while((len = fill_buf(buf, BUF_SIZE)) > 0)
		if(len > 1)
			if(buf[len-2] != ' ' && buf[len-2] != '\t')
				printf("%s", buf);
			else if(buf[len-1] == '\n')
				printf("\n");

	exits(0);
}
   
int
fill_buf(char s[], int lim)
{
	int c, i;
	int has_non_blank;

	has_non_blank = 0;
	for(i = 0; 
		i < lim-1 &&
			(c=getchar())!=EOF &&
			c != '\n' &&
			(!has_non_blank || (c != ' ' && c != '\t')); 
		++i) {

		// printf("#%c\n", c);

		s[i] = c;

		has_non_blank = c != ' ' && c != '\t';

	}
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
