#include <u.h>
#include <libc.h>
#include <stdio.h>

#define LIM 100

void
main(void)
{
	int i, ok;
	char s[LIM], c = '\0';
	
	ok = 1;
	i = 0;
	while(ok) {
		if(i < LIM-1)
			if((c=getchar()) != '\n')
				if(c != EOF) {
					s[i] = c;
					i++;
				}
				else
					ok = 0;
			else
				ok = 0;
		else
			ok = 0;
	}

	if(c != EOF) {
		s[i] = c;
		i++;
	}

	printf("%s", s);
}
