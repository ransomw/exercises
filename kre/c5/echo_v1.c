#include <u.h>
#include <libc.h>
#include <stdio.h>

/* this is from 5.10 Command-line Arguments */

/**
 * echo command-line arguments on a single line,
 * separated by blanks
 */

/* argc for 'argument count' is the number of command-line
 * arguments.
 * argv for 'argument vector' is an array of character strings,
 * one per command-line argument
 *
 * argv[0] is the name of the executable,
 * so argc > 0, argv[1] is the first optional argument,
 *	and argv[argc-1] is the last.
 *
 * the language standard also provides argv[argc] == NULL
 */
void
main(int argc, char *argv[])
{
	int i;

	for(i = 1; i < argc; i++)
		printf("%s%s", argv[i],
			(i < argc - 1) ? " " : "");
	printf("\n");

	exits(0);
}
