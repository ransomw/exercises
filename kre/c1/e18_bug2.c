#include <u.h>
#include <libc.h>
#include <stdio.h>

#define BUF_SIZE	1000
#define IN_LINE		1
#define OUT_LINE	0

int fill_buf(char s[], int lim);

/**
 * debugging e18_bug1.c:  add state to solve the EOL problem.
 * new bug:
'asdf  qwer'
 * produces output
'asdf qwer'
 * the bug about tab stops in _bug1.c is not present,
 * an artifact of rio/rc auto-indent.
 */
void
main(void)
{
	int len;
	char buf[BUF_SIZE];
	int state_line;

	state_line = OUT_LINE;
	while((len = fill_buf(buf, BUF_SIZE)) > 0)
		if(len > 1)
			if(buf[len-2] != ' ' && buf[len-2] != '\t') {
				printf("%s", buf);
				if(buf[len-1] != '\n')
					state_line = IN_LINE;
				else
					state_line = OUT_LINE;
			}
			else if(buf[len-1] == '\n' &&
					state_line == IN_LINE) {
				printf("\n");
				state_line = OUT_LINE;
			}

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
		s[i] = c;
		// todo: dedupe
		has_non_blank = c != ' ' && c != '\t';
	}
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
