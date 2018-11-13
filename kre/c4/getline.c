#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINE	1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

void
main(void)
{
	char line[MAXLINE];
	int found = 0;

	while(getline(line, MAXLINE) > 0)
		if(strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}

	if(found)
		exits(0);
	else
		exits("no match");
}

int
getline(char s[], int lim)
{
	int c = EOF, i;

	i = 0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* index of t in s */
int
strindex(char s[], char t[])
{
	int i, j, k;

	for(i = 0; s[i] != '\0'; i++) {
		for(j=i, k=0;
			t[k] != '\0' && s[j] == t[k];
			j++, k++)
			;
		if(k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

/* function definitions have the form
 *	<return-type> <function-name>(<parameter declarations>)
 *	{
 *		<declarations and statements>
 *	}
 */

/* parameter declarations can be omitted */

/* if the return type is omitted, int is assumed,
 * and the plan 9 compiler does not allow the return statement
 * to be omitted.
 */
get_one()
{
	/* the return statement has the general form
	 *	return <expr>
	 * any --- or no ---  expression may follow return,
	 * and the expression will be converted
	 * to the return type of the function.
	 */
	return -2 + 3;
}

/* void functions needn't have a return statement
 */
void noop() {  }
