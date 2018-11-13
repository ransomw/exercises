#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

void
main(void)
{
	printf("%.3f\n", atof(""));
	printf("%.3f\n", atof("1.23"));
	printf("%.3f\n", atof("12.3e-1"));
	printf("%.3f\n", atof(".0123e2"));
	printf("%.3f\n", atof("1230000000e-9"));
	printf("%.3f\n", atof("12300000000e-10"));
	exits(0);
}



double
atof(char s[])
{
	double val, power;
	int i, j, sign, exp, sign_exp;

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
	if(s[i] == 'e')
		i++;
	sign_exp = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(exp = 0; isdigit(s[i]); i++)
		exp = 10 * exp + (s[i] - '0');
	for(j = 0; exp > j; j++)
		if(sign_exp < 0)
			power *= 10;
		else
			power /= 10;
	return sign * val / power;
}
