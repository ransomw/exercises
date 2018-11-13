#include <u.h>
#include <libc.h>

void
swap(char *x, char *y)
{
	char tmp;
	
	tmp = *x;
	*x = *y;
	*y = tmp;
}

char *
reverse(char *s)
{
	char *l, *r;

	l = r = s;
	while(*r != '\0')
		r++;
	for(;l < --r; l++)
		swap(l, r);
	return s;
}
