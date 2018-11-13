#include <u.h>
#include <libc.h>
#include <stdio.h>
#define MAXLINE	1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

void
main(void)
{
	char line[MAXLINE];
	int found = 0;

	while(getline(line, MAXLINE) > 0)
		if(strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}

	if(found)
		exits(0);
	else
		exits("no match");
}
