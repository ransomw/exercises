#include <u.h>
#include <libc.h>
#include <stdio.h>

void printd(int);
void mqsort(int[], int l, int r);

void
main(void)
{
	int i;
	int xs[] = {3, 9, 3, 5};

	mqsort(xs, 0, 3);
	printd(123);
	putchar('\n');
	for(i = 0; i < 4; i++)
		putchar('0' + xs[i]);
	putchar('\n');

	exits(0);
}

/* printd: print an integer in decimal (base 10) notation */
void printd(int n)
{
	int rest;
	/* as with itoa, this fails on the largest
	 * negative number in two's compliment systems
	 */
	if(n < 0) {
		putchar('-');
		n = -n;
	}
	if(rest = n / 10)
		/* print all digits except the first */
		printd(rest);
	putchar(n % 10 + '0');
}

/* qsort(2) */ 
void mqsort(int v[], int left, int rite)
{
	int i, last;
	/* recall function declarations can be internal,
	 * just as variable declarations
	 */
	void swap(int v[], int i, int j);
	if(left >= rite)
		return;
	/* move the element to sort around off to one side */
	swap(v, (left + rite)/2, left);
	/* keep track of where the sorted elements are */
	last = left;
	for(i = left + 1; i <= rite; i++)
		if(v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	/* now everything left of last is < left
	 * and everything on the other side is >= left
	 */
	mqsort(v, left, last - 1);
	mqsort(v, last + 1, rite);
}

void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
