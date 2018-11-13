#include <u.h>
#include <libc.h>
#include <stdio.h>

int any(char s1[], char s2[]);

void
main(void)
{
	printf("%d == -1 and %d == 2\n", 
		any("asdf", "qwer"), 
		any("asdf", "qwerdy"));

	exits(0);
}

/* returns: an index to 
 * the first location in s1 where any character from s2 occurs
 * or -1 if s1 contains no characters from s2
 *
 * stdlib contains strpbrk, an analogous function that returns
 * a pointer to the location rather an index
 */
int
any(char s1[], char s2[])
{
	int i, k, c, n;

	n = -1;
	for(k = 0; (c = s2[k]) != '\0'; ++k)
		for(i = 0; s1[i] != '\0'; i++)
			if(s1[i] == c && (i < n || n == -1))
				n = i;
				
	return n;
}

// todo: revisit impl (current is modified e4, read strpbrk
