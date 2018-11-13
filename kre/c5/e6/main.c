#include <u.h>
#include <libc.h>
#include <stdio.h>

char *reverse(char *);
int strindex(char *, char *);

void
main(void)
{
	printf("'%s' %s %s %s %s %s\n",
		reverse(""),
		reverse("q"),
		reverse("qw"),
		reverse("qwe"),
		reverse("qwer"),
		reverse("qwert"));

	printf("8 %d\n", strindex("asdfasdfqwer", "qwer"));
	printf("12 %d\n", strindex("asdfqwerasdfqwer", "qwer"));
	printf("-1 %d\n", strindex("asdfasdfqwer", "qwert"));
	printf("-1 %d\n", strindex("a", ""));
	printf("-1 %d\n", strindex("", "a"));


	exits(0);
}
