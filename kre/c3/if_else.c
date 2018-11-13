/* the if-else statement has syntax
 *
 *	if(<expr>)
 *		<statement>_1
 *	else
 *		<statement>_2
 *
 * where the '`else` part',
 *	else
 *		<statement>_2
 * is optional.
 * to evaluate the statement, <expr> is evaluated, and
 * if <expr> has non-zero value, <statement>_1 is executed.
 * otherwise, <statement>_2 is executed if the `else` part
 * is present.
 */

if(expr)
/* is equivalent to */
if(expr != 0)
/* although which form is clearer is context-dependent */

/* nested `if` sequences can be tricky since the `else`
 * part is optional. there's a formal rule, namely,
 *
 * the `else` part in a nested sequence of `if`s is associated
 * with the inner `if`
 *
 * however, it's not always clear in practice.  for example,
 */
if(n > 0)
	if(a > b)
		z = a;
	else
		z = b;
/* runs as expected for the given indentation.
 *
 * braces can be used to associate the `else` part to the outer `if`
 */
if(n > 0) {
	if(a > b)
		z = a;
}
else
	z = b;
/* however, since whitespace doesn't affect evaluation,
 * indentation can be misleading.
 * for example,
 */
if(n > 0)
	for(i = 0; i < n; ++i)
		if(s[i] > 0) {
			printf("...");
			return i;
		}
else
	printf("error -- n is negative\n");
/* is incorrect.  the correct indentation and printf message are */
if(n > 0)
	for(i = 0; i < n; ++i)
		if(s[i] > 0) {
			printf("...");
			return i;
		}
		else
			printf("error -- s[i] is negative\n");
/*
 * because of this kind of thing,
 * using braces whenever there are nested `if`s is good practice.
 */
