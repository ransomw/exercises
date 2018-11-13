#include <u.h>
#include <libc.h>
#include <stdio.h>

void expand(char s[], char t[]);

void
main(void)
{
	char s1[] = "zxcva-zqwer";
	char s2[] = "a-b-c";
	char s3[] = "a-z0-9";
	char s4[] = "-a-z";
	char t[100];
	
	expand(s1, t);
	printf("%s : %s\n", s1, t);
	expand(s2, t);
	printf("%s : %s\n", s2, t);
	expand(s3, t);
	printf("%s : %s\n", s3, t);
	expand(s4, t);
	printf("%s : %s\n", s4, t);
}

void
expand(char s[], char t[])
{
	int i, j, c, c1, c2, c3;
	i = j = 0;
	while((c1 = s[i++]) != '\0') {
		/* lookahead for expansion pattern */
		if((c2 = s[i]) == '-' &&
			(c3 = s[i+1]) != '\0' &&
			c3 > c1) {
			i += 2;
			for(c = c1; c <= c3; j++, c++)
				t[j] = c;		
		} else {
			t[j++] = c1;
		}
	}
	t[j] = '\0';
}
