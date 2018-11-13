#include <u.h>
#include <libc.h> /* contains strstr, in string.h on *nix */
#include <stdio.h>
#define MAXLINE	1000 /* max chars per line */

int getline(char *s, int max);

void
main(int argc, char *argv[])
{
	char line[MAXLINE];
	int lineno = 0;
	int c, except =0, number = 0, found = 0;

	/* plan 9 programs typically use a particular
	 * preprocessor definition to process cl args.
	 * this example is included from the text as is
	 * in order to include the following example
	 * of pointer arithmetic:
	 *
	 * [] binds tighter than * and ++, so
	 * `*++argv[0]` means `*++(argv[0])`.
	 * that is, the pointer contained stored in argv[0]
	 * is incremented by the inner loop.
	 *
	 * meanwhile, the outer loop increments the pointer
	 * to the current argument string (a char *).
	 * in particular, remember that array and pointer
	 * notations are equivalent in fn parameter declarations.
	 *
	 * hidnu.
	 */
	char **margv = argv;
	while(--argc > 0 && (*++margv)[0] == '-') {
		while(c = *++margv[0])
			switch(c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("illegal option %c\n", c);
				exits("illegal option");
				argc = 0;
				found = -1;
				break;
			}
	}


	if(argc != 1) {
		printf("Usage: find [-x] [-n] pattern\n");
		exits("usage");
	}

	while(getline(line, MAXLINE) > 0) {
		lineno++;
		/* idiom to negate boolean according to flag */

		if((strstr(line, *margv) != NULL) != except) {
			if(number)
				printf("%d:", lineno);
			printf("%s", line);
			found++;
		}
	}
	if(!found)
		exits("no match");
	exits(0);
}

int
getline(char *s, int lim)
{
	int c = EOF;
	char *start = s;

	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = c;
	*s = '\0';
	return s - start;
}
