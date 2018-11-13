#include <u.h>
#include <libc.h>
#include <stdio.h>

#define swap(T, X, Y)	{\
T temp; \
temp = X; \
X = Y; \
Y = temp; \
}

void
main(void)
{
	int a, b;
	double x, y;
	/* note first that compound statements can be used
	 * apropos of nothing, i.e. a block needn't follow
	 * a conditional or loop construct
	 */
	char s[] = "world";
	{
		char s[] = "rick";
		printf("hello %s\n", s);
	}
	printf("hello %s\n", s);

	a = 1; b = 2;
	printf("%d %d\n", a, b);
	swap(int, a, b);
	printf("%d %d\n", a, b);

	y = 1.23; x = 3.21;
	printf("%g %g\n", y, x);
	swap(double, y, x);
	printf("%g %g\n", y, x);

	exits(0);
}
