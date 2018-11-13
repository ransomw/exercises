#include <u.h>
#include <libc.h>
#include <stdio.h>

void squeeze(char s[], int c);

void
main(void)
{
	int n, m;

	/* increment and decrement operators 
	 * can be prefix or postfix
	 */
	n = m = 0;
	++n; n++;
	--m; m--;
	printf("%d %d\n", n, m);

	/* the prefix changes the value before it is used
	 * while the postfix changes it after
	 */
	n = m = 0;
	m = n++; // m == 0
	printf("%d %d\n", n, m);
	n = m = 0;
	m = ++n; // m == 1
	printf("%d %d\n", n, m);

	char s[] = "asadaf";
	squeeze(s, 'a');
	printf("%s\n", s);
	strcat(s, "321");
	printf("%s\n", s);	

	exits(0);
}

/* delete all c from s */
void
squeeze(char s[], int c)
{
	int i, j;

	for(i = j = 0; s[i] != '\0'; i++)
		if(s[i] != c)
			s[j++] = s[i];

	s[j] = '\0';
}

/* delete all c from s */
void
squeeze_equiv(char s[], int c)
{
	int i, j;

	for(i = j = 0; s[i] != '\0'; i++)
		if(s[i] != c) {
			s[j] = s[i];
			j++;
		}

	s[j] = '\0';
}

int
getline(char s[], int lim)
{
	int c, i;

	for(i = 0; 
		i < lim-1 && 
			(c=getchar())!=EOF && 
			c != '\n'; 
		++i)
		s[i] = c;
	if(c == '\n')
		/* another example of postfix increment
		 * replaces two statements with one
		 * in this modified function from c1/print_longest.c
		 */
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* concat t onto the end of s.
 * supposes enough memory is allocated for s.
 *
 * there's a stdlib version that returns
 * (a pointer to) a new string.  this version is only
 * to demonstrate use[fulness] of the postfix increment.
 */
void
my_strcat(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while(s[i] != '\0')
		i++;
	while((s[i++] = t[j++]) != '\0')
		;
}
