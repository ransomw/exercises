#include <ctype.h>

double
atof(char s[])
{
	double val, power;
	int i, sign;

	/* skip white space, if any */
	for(i = 0; isspace(s[i]); i++)
		;
	/* get sign, if any */
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}

int
atoi(char s[])
{
	double atof(char s[]);
	/* 8c, the plan 9 compiler, doesn't warn if the cast
	 * is omitted.  typecasting still documents that
	 * returning an int is intended, even though the function
	 * type automatically casts the return value.
	 */
	return (int) atof(s);
}
