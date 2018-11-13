#include <u.h>
#include <libc.h>
#include <stdio.h>
#define ALLOCSIZE	10000 /* size of available addr space */

/* example from the address arithmetic section ---
 * these functions maintain a stack of memory
 * that can be both handed out and reclaimed
 * by the rest of the program.
 */

char *alloc(int n);
void afree(char *p);


void
main(void)
{
	char *s, *t, *u;

	/* the name NULL is defined in stdio.h as 0
	 * with the intent of being a "mnemonic" to
	 * indicate that 0 is being used as a pointer
	 * value.  see comments on alloc return statements below
	 */ 
	printf("NULL == %d\n", NULL);

	/* alloc sets aside some memory on the stack
	 * and returns a pointer to the beginning of it
	 */
	s = alloc(100);
	if(s != NULL)
		/* notice that using string literals as in
		 * s = "hi" does *not* write to the memory
		 * addresses managed by alloc and free.
		 * more on this anon.
		 */
		s[0] = 'h', s[1] = 'i', s[2] = '\0';
	t = alloc(100);
	if(t != NULL)
		t[0] = 'w', t[1] = 'r', t[2] = '\0';
	printf("%s, %s\n", s, t);

	/* afree rewinds the stack to the beginning of the
	 * memory allocated to its parameter, usually
	 * a return value of alloc.  here, some silliness.
	 */
	afree(t + 1);
	u = alloc(100);
	if(u != NULL)
		u[0] = 't', u[1] = 'h', u[2] = '\0';
	printf("%s, %s\n", s, u);
	/* since the some of the memory allocated to t has been
	 * freed, t's value can be considered "garbage" ..
	 * .. or something.  idk, just re-read pts_and_arrays.
	 */
	printf("%s, %s\n", s, t);
	
	

	exits(0);
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *
alloc(int n)
{
	/* note that, in addition to the - operator,
	 * comparison operators ==, !=, <, >, <=, >=
	 * also apply to pointers, because the address
	 * space is linerarly ordered.
	 */
	if(allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		/**** 0 is never a valid memory address ****/
		return allocp - n;
	} else
		/* conversely, 0 is the only valid integer literal
		 * that can be assigned to a pointer variable.
		 */
		return 0;
}

void
afree(char *p)
{
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/* section 8.7 covers a more replete implementation
 * of malloc, a standard library function.
 */
