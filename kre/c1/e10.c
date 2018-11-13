#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	int c;

	while((c = getchar()) != EOF) {
		if(c == '\t')
			print("\\t");
		if(c == '\b')
			print("\\b");
		// else, logical ops not introduced
		if(c != '\t')
			if(c != '\b')
				putchar(c);
	}

	exits(0);
}
