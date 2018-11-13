#include <u.h>
#include <libc.h>
#include <stdio.h>

/* when initialization of external variables
 * is present, it must be a constant, because in the
 * absence of calling a function, no computation occurs.
 *
 * it is less obvious and also the case that `static`
 * variables' initialization must be a constant expression,
 * presumably because of ease of implementation.
 *
 * to whit, computation of external and static variables'
 * initialization occurs *before execution*, so computation
 * of constant expressions such as `1 + 1` can occur,
 * while the compiler *cannot* figure out even
	static int x = 1;
	static int y = x + 1;
 *
 * by contrast, internal/automatic variables are easy:
	int x;
	x = 1;
 * is equivalent to
	int x = 1;
 * i.e. initialization can be viewed as syntatic sugar
 * for assignment.
 */
int ex;

void
main(void)
{
	/* when initializing arrays with a literal upon
	 * declaration, it's permissable to omit the length
	 * of the array in the declaration.  e.g., */
	int days[] = { 31, 28, 31, 30, 31, 30, 31,
			31, 30, 31, 30, 31 };
	/* can be used instead of 
	int days[12] = {31, ..., 31};
	*/

	/* at initialization, string literals are
	 * equivalent to '\0'-terminated array literals
	 * of characters.  this equivalence is *not*
	 * true on function (e.g. printf()) calls.
	 */
	char msg[] = {'h', 'e', 'l', 'l', 'o', '\0'};
	
	static int stat;
	int ar[2] = {1};

	printf("%s\n", msg);
	printf("external %d and static %d variables ", ex, stat);
	printf("initialize to zero by default,\n");
	printf("as are array values %d ", ar[1]);
	printf("wherever they occur.\n");
	/* by constrast, internal variables' initial values
	 * are undefined
	 */

	printf("Jan %d Feb %d Mar %d\n",
		days[0], days[1], days[2]);
	printf("Apr %d May %d Jun %d\n",
		days[3], days[4], days[5]);
	printf("Jul %d Aug %d Sep %d\n",
		days[6], days[7], days[8]);
	printf("Oct %d Now %d Dec %d\n",
		days[9], days[10], days[11]);

	exits(0);
}
