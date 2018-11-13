#include <u.h>
#include <libc.h> /* contains strstr, in string.h on *nix */
#include <stdio.h>
#define MAXLINE	1000 /* max chars per line */

int getline(char *s, int max);

void
main(int argc, char *argv[])
{
	char line[MAXLINE];
	int found = 0;

	if(argc != 2) {
		printf("Usage: find pattern\n");
		exits("usage");
	}
	while(getline(line, MAXLINE) > 0)
	/* strstr(char *s, char *t)
	 * returns a pointer to the first occurence of t in s
	 *	or NULL if t doesn't occur in s
	 */
		if(strstr(line, argv[1]) != NULL) {
			printf("%s", line);
			found++;
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
