#include <u.h>
#include <libc.h>
#include <stdio.h>

int trimr(char s[]);
int sum_pos(int xs[], int n);

void
main(void)
{
	int zs[] = {1, -2, 3, -4, 5};
	char s1[] = "         ";
	char s2[] = "asfd     ";
	char s3[] = "";

	printf("%d\n", sum_pos(zs, 5));

	trimr(s1);
	trimr(s2);
	trimr(s3);
	printf("'%s' '%s' '%s'\n", s1, s2, s3);
}

/* trimr: remove trailing whitespace */
int
trimr(char s[])
{
	int n;

	for(n = strlen(s)-1; n >= 0; n--)
		if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
			/* causes *innermost* loop
			 * (for, while, or do) or switch
			 * to exit immediately
			 */
			break;
	s[n+1] = '\0';
	return n;
}

/* sum_pos: sum positive elements */
int
sum_pos(int xs[], int n)
{
	int i, sum = 0;
	for(i = 0; i < n; i++) {
		if(xs[i] < 0)
			/* begin next iteration of enclosing loop
			 * in for loops, this means the increment
			 * step.  in while and do loops, the test.
			 */
			continue;
		sum += xs[i];
	}
	return sum;
}
