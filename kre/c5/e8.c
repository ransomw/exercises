#include <u.h>
#include <libc.h>
#include <stdio.h>

int day_of_year(int y, int m, int d);
int month_day(int y, int yd, int *m, int *md);


void
main(void)
{
	int year = 2021, month = 10, day = 31;
	int year_day;

	/* checks on functionality with valid params
	 */	
	printf("%d-%d-%d\n", year, month, day);
	year_day = day_of_year(year, month, day);
	month_day(year, year_day, &month, &day);
	printf("%d-%d-%d\n", year, month, day);
	year_day++;
	month_day(year, year_day, &month, &day);
	printf("%d-%d-%d\n", year, month, day);

	/* compare with invalid days below */
	month_day(year = 1984, 366, &month, &day);
	printf("%d-%d-%d\n", year, month, day);
	month_day(year = 1981, 365, &month, &day);
	printf("%d-%d-%d\n", year, month, day);

	/* checks on error-handling
	 */
	printf(("day_of_year: "
		"invalid month error %d %d\n"),
		day_of_year(2021, 13, 1),
		day_of_year(2021, 0, 1));
	printf(("day_of_year: "
		"invalid day error %d %d\n"),
		day_of_year(2021, 10, -1),
		day_of_year(2021, 9, 31));

	printf(("month_day: "
		"invalid day error %d %d\n"),
		month_day(1984, 367, &month, &day),
		month_day(1981, 366, &month, &day));

	exits(0);
}

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
	/* begin error-handling */
	if(month < 1 || month > 12)
		return -1;
	if(day < 1 || day > daytab[leap][month])
		return -2;
	/* end error-handling */
	for(i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

int
month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = leap_year(year);
	for(i = 1; yearday > daytab[leap][i]; i++) {
		if(i == 12)
			return -1;
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
	return 0;
}
