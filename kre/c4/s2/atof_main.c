#include <u.h>
#include <libc.h>
#include <stdio.h>

double atof(char s[]);
int atoi(char s[]);

void
main(void)
{
	printf("%.3f\n", atof("1.23"));
	printf("%d\n", atoi("31.2"));
	exits(0);
}
