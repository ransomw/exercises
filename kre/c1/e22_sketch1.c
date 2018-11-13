#include <u.h>
#include <libc.h>
#include <stdio.h>

/* maximum characters before "fold" */
#define MAX_LEN	20
#define TAB_WIDTH 4

void
main(void)
{
	int len, ilen, tlen, lc;
	char buf[MAX_LEN + 1];

	tlen = 0; // length of curr line thus far
	while((len = fill_buf(buf, MAX_LEN)) > 0) {
		lc = buf[len-1];
		if(lc == ' ' || lc == '\t' || lc =='\n')
			ilen = len - 2;
			buf[len-1] = '\0;
		else
			ilen = len - 1;
	}

	exits(0);
}

int
fill_buf(char buf[], int len)
{
	int i, c;

	for(i=0; (c=getchar()) != EOF &&
		c != ' ' && c != '\t' && c !='\n' &&
		i < len; ++i)
		buf[i] = c;

	if(c != EOF) {
		buf[i] = c;
		++i;
	}
	buf[i] = '\0';

	return i;
}
