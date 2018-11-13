#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	int c;
	int pc = EOF;

	while((c = getchar()) != EOF) {
		if(pc == ' ')
			if(c != ' ')
				putchar(c);
		if(pc != ' ')
			putchar(c);
		pc = c;
	}

	exits(0);
}
