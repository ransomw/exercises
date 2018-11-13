#include <u.h>
#include <libc.h>

/* leftmost index of t in s starting at i */
int
strlindex(char *s, char *t, int i)
{
	char *start;
	char *u, *v;

	start = s;
	for(s += i; *s != '\0'; s++) {
		for(u = s, v = t;
			*v != '\0' && *u == *v;
			u++, v++)
			;
		if(v - t > 0 && *v == '\0')
			return s - start;
	}
	return -1;
}


/* rightmost index of t in s */
int
strindex(char *s, char *t)
{
	int i, index;

	i = index = -1;
	while((i = strlindex(s, t, index + 1)) != -1)
		index = i;
	return index;
}
