#include <u.h>
#include <libc.h>
#include <stdio.h>

void squeeze(char s1[], char s2[]);

void
main(void)
{
	char s[] = "asdfdsa";
	squeeze(s, "qwersfs");
	printf("%s\n", s);

	exits(0);
}

// todo: consider perf when s2 has repeated characters
/* delete each character in s1 that matches any character in s2 */
void
squeeze(char s1[], char s2[])
{
	int i, j, k, c;

	for(k = 0; (c = s2[k]) != '\0'; ++k) {
		for(i = j = 0; s1[i] != '\0'; i++)
			if(s1[i] != c)
				s1[j++] = s1[i];
		s1[j] = '\0';
	}
}
