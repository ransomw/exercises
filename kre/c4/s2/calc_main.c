#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINE	100

void
main(void)
{
	/* function declarations may occur in functions */
	double sum, atof(char []);
	char line[MAXLINE];
	/* this declaration cannot be omitted,
	 * although it can be changed (e.g. to float rather
	 * than int return type), because the files are compiled
	 * separately.
	 * the program in a given file treats functions' return
	 * types as declared, but the function returns types
	 * according to its definition.  so mismatched definitions
	 * and declarations are a source of bugs.
	 */
	int getline(char line[], int max);

	sum = 0;
	while(getline(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
	exits(0);
}
