
/**
 * convert between number of days throughout the year
 * and number of months throughout the year plus
 * days throughout the month
 */

/* this is an array of `char`s to illustrate a reasonable use of
 * `char` to store non-`char` integers, namely `char` is used
 * when the integers are known to be small enough to fit in a
 * signed byte.
 *
 * this is the first use of a two-dimensional array.
 * a two-dimensional array is a one dimensional array,
 * each element of which is an array, so the notation is
	array[row][col]
 * not
	array[row, col]
 *
 * elements are stored in memory a row-at-a-time,
 * so `a[i][j+1]` are the cells after `a[i][j]` in memory space.
 *
 * note the initialization of two-dimension arrays by literals
 * is done with sub-lists, not a flat list of each row
 * concatenated with the next.
 *
 *
 * when passing a two-dimensional array to a function,
 * the number of columns must be included.  the number
 * of rows can be included but is not relevant, so
 	f(int daytab[2][13]) {}
	f(int daytab[][13]) {}
	f(int (*daytab)[13])
 * are all valid parameter declarations.  the last says
 * that the parameter is a pointer to an array of 13 integers.
 * that is,
 * the number of rows must be included, because the function
 * recvs a [non-void] pointer, and [non-void] pointers correspond
 * to a type with size information.
 *
 * to reiterate,
	int *daytab[13]
 * says daytab is an array of pointers to integers
	int (*daytab)[13]
 * says daytab is a pointer to an array of integers.
 * this is a consequence of precendence:  brackets [] have
 * higher precedence than the deref-mnmonic *.
 */
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* 1 if year is a leap year, 0 otherwise */
int
leap_year(int year)
{
	return year % 4 == 0 && 
		year % 100 != 0 || 
		year % 400 == 0;
}

int
day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = leap_year(year);
	for(i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void
month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = leap_year(year);
	for(i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
