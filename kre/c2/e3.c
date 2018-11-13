#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);
int hex_digit_to_int(char c);

void
main(void)
{

	printf("%x %x %x\n",
		htoi("0x9FAD"),
		htoi("OX9FAD"),
		htoi("9FAD"));

	printf("%x\n", htoi("0"));

	exits(0);
}

int
htoi(char s[])
{
	int i, n;

	i = n = 0;
	if((s[0] == '0' && s[1] =='x') || 
		(s[0] == 'O' && s[1] =='X'))
		i = 2;

	for(; s[i] != '\0'; ++i)
		n = 16 * n + hex_digit_to_int(s[i]);

	return n;
}

int
hex_digit_to_int(char c)
{
	if(isdigit(c))
		return c - '0';

	if('A' <= c && c <= 'F')
		return 10 + (c - 'A');

	if('a' <= c && c <= 'f')
		return 10 + (c - 'a');

	return 0;
}
