#include <u.h>
#include <libc.h>
#include <stdio.h>

#define MAX_STR_LEN	100

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

void
main(void)
{
	char s1[] = "asdf";
	char s2[] = "\a\\\"\\\\";
	char t1[MAX_STR_LEN], t2[MAX_STR_LEN];
	char u1[MAX_STR_LEN], u2[MAX_STR_LEN];

	escape(s1, t1);
	escape(s2, t2);
	unescape(t1, u1);
	unescape(t2, u2);

	printf("%s %s\n", s1, s2);
	printf("%s %s\n", t1, t2);
	printf("%s %s\n", u1, u2);
}

/* characters to escape sequences */
void
escape(char s[], char t[])
{
	int i, j;
	i = j = 0;
	while(s[i] != '\0') {
		t[j++] = '\\';
		switch(s[i]) {
		case '\a': // alert (bell)
			t[j] = 'a';
			break;
		case '\b': // backspace
			t[j] = 'b';
			break;
		case '\f': // formfeed
			t[j] = 'f';
			break;
		case '\t': // horizontal tab
			t[j] = 't';
			break;
		case '\v': // vertical tab
			t[j] = 'v';
			break;
		case '\\': // backslash
			t[j] = '\\';
			break;
		case '\?': // question mark
			t[j] = '?';
			break;
		case '\'': // single quote
			t[j] = '\'';
			break;
		case '\"': // double-quote
			t[j] = '\"';
			break;
		case '\r': // carriage return
			t[j] = 'r';
			break;
		case '\n': // newline
			t[j] = 'n';
			break;
		default:
			j--;
			t[j] = s[i];
			break;
		}
		i++;
		j++;
	}
}


/* escape sequences to character */
void
unescape(char s[], char t[])
{
	
}
