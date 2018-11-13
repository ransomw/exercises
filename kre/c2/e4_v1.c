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

/* delete all c from s */
void
squeeze_char(char s[], int c)
{
	int i, j;

	for(i = j = 0; s[i] != '\0'; i++)
		if(s[i] != c)
			s[j++] = s[i];

	s[j] = '\0';
}


/* delete each character in s1 that matches any character in s2 */
void
squeeze(char s1[], char s2[])
{
	int i, c;

	for(i = 0; (c = s2[i]) != '\0'; ++i)
		squeeze_char(s1, c);
}
