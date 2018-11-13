#include <u.h>
#include <libc.h>
#include <stdio.h>

int binsearch(int x, int v[], int n);
int my_binsearch(int x, int v[], int n);

// todo: mor tests
// todo, ???: how to time function calls?
void
main(void)
{
	int v1[] = {1, 3, 7, 8, 9};
	int v2[] = {1, 3, 5, 7, 8, 9};

	printf("binsearch | my_binsearch\n");
	printf("------------------------\n");
	printf("   %d           %d\n",
		binsearch(3, v1, 5), my_binsearch(3, v1, 5));
	printf("   %d           %d\n",
		binsearch(8, v1, 5), my_binsearch(8, v1, 5));
	printf("   %d           %d\n",
		binsearch(10, v1, 5), my_binsearch(10, v1, 5));
	printf("   %d           %d\n",
		binsearch(9, v1, 5), my_binsearch(9, v1, 5));

	printf("   %d           %d\n",
		binsearch(3, v2, 6), my_binsearch(3, v2, 6));
	printf("   %d           %d\n",
		binsearch(8, v2, 6), my_binsearch(8, v2, 6));
	printf("   %d           %d\n",
		binsearch(10, v2, 6), my_binsearch(10, v2, 6));
	printf("   %d           %d\n",
		binsearch(9, v2, 6), my_binsearch(9, v2, 6));

	// binsearch(2, v1, 5);
	/* the following function call does not return
	 * 	binsearch(2, v1, 5)
	 */
	printf("\nexpected | my_binsearch\n");
	printf("------------------------\n");
	printf("   %d           %d\n",
		-1, my_binsearch(2, v1, 5));
	printf("   %d           %d\n",
		-1, my_binsearch(5, v1, 5));

	exits(0);
}

int
binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low+high)/2;
		if(x < v[mid])
			high = mid + 1;
		else if(x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int
my_binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low < high - 1) {
		mid = (low+high)/2;
		if(x < v[mid])
			high = mid-1;
		else
			low = mid;
	}
	if(x == v[low])
		return low;
	else if(x == v[high])
		return high;
	else
		return -1;
}
