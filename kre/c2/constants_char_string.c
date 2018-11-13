#include <u.h>
#include <libc.h>
#include <stdio.h>

/* internal impl of standard library strlen() */
int my_strlen(char s[]);

void
main(void)
{
	/* character constants are integers */
	printf("%d %c%c\n", '0', '0', 48);

	/* there are a 11 special escape sequences */
	printf("%c %c %c %c %c %c %c %c %c %c %c",
		'\a', // alert (bell)
		'\b', // backspace
		'\f', // formfeed
		'\t', // horizontal tab
		'\v', // vertical tab
		'\\', // backslash
		'\?', // question mark ??? why does this need escape?
		'\'', // single quote
		'\"', // double-quote
		'\r', // carriage return
		'\n'); // newline

	/* three-digit octal and one or two-digit hex
	 * escape sequences are also valid char constants.
	 */
	printf("%o %x %x %x\n",
		'\013',
		'\xb',
		'\x9',
		'\x1a');
	/* not all valid escape sequences are available, however,
	 * since char constants are still char-sized
	 * (cf. type_conversions.c)
	 */
	printf("%o %o %o\n",
		'\177', '\200', 0200);
	printf("%x %x %x\n",
		'\x7f', '\x80', 0x80);

	/* the null character is zero.
	 * '\0' is used for clarity of intent.
	 */
	printf("'%c' %d\n",
		'\0', '\0');

	/* string constants are surrounded by double-quotes
	 * and use the same escape sequences as character constants
	 */
	printf("%s",
		"\a\b\f\t\v\\\?\'\"\r\177\x7f\n");

	/* strings are arrays of characters
	 * with a '\0' added at the end
	 */
	printf("%d\n",
		my_strlen("asdf"));
	/* in particular, 'x' is not the same as "x".
	 * the former is an integer, the latter is an array.
	 */

	exits(0);
}

int
my_strlen(char s[])
{
	int i;

	while(s[i] != '\0')
		++i;
	return i;
}
