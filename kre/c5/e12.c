#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#define TAB_WIDTH	8
#define MAXSTOPS	10

void detab(int, int *, int);
void entab(int, int *, int);

void
main(int argc, char *argv[])
{
	int isdetab = 0;
	/* tab stops every so many columns */
	int tse = -1;
	/* tab stop starting point on these tabs */
	int tses = -1;
	int ntws, tws[MAXSTOPS], twstot;
	int i, c;

	while(--argc > 0 && ((*++argv)[0] == '-' ||
				(*argv)[0] == '+')) {
		if((*argv)[0] == '+') {
			if((tse = atoi(*argv + 1)) < 1)
				exits("invalid tab-every width");
			continue;
		}
		if(isdigit((*argv)[1])) {
			if((tses = atoi(*argv + 1)) < 1)
				exits("invalid tab start");
			continue;
		}
		while(c = *++argv[0])
			switch(c) {
			case 'd':
				isdetab = 1;
				break;
			default:
				printf("illegal option %c\n", c);
				exits("illegal option");
			}
	}
	if(argc > MAXSTOPS)
		exits("too many tab stops");
	twstot = 0;
	for(i = 0; i < argc; i++)
		if((tws[i] = atoi(argv[i])) < 0)
			exits("invalid tab width");
		else
			twstot += tws[i];
	/* todo: test no tab stop list params here and in e11
	 *	(and probably debug by setting ntws = argc
	 */
	ntws = argc == 0 ? 1 : argc;

	/* design consideration: check == -1 here instead? */
	tse = tse < 1 ? TAB_WIDTH : tse;
	if(tses < 0 || tses == twstot)
		tws[i] = TAB_WIDTH;
	else if(tses < twstot)
		exits("manual+auto tab-width param mismatch");
	else {
		tws[ntws++] = tses - twstot;
		tws[ntws] = tse;
	}

	if(isdetab)
		detab(ntws, tws, tse);
	else
		entab(ntws, tws, tse);

	exits(0);
}

/* ntws - number tab widths
 * tws - tab widths
 * dtw - default tab width
 */
void
detab(int ntws, int tws[], int dtw)
{
	int c, rem;
	/* current tab width */
	int *ctw;

	ctw = tws;
	rem = *ctw;
	while((c = getchar()) != EOF) {
		switch(c) {
		case '\n':
			if(putchar(c) == EOF)
				exits("putchar");
			ctw = tws;
			rem = *ctw;
			break;
		case '\t':
			for(; rem > 0; --rem)
				if(putchar(' ') == EOF)
				exits("putchar");
			break;
		default:
			if(putchar(c) == EOF)
				exits("putchar");
			--rem;
			break;
		}
		if(rem == 0) {
			if(ctw != &dtw && ctw - tws < ntws)
				ctw++;
			else
				ctw = &dtw;
			rem = *ctw;
		}
	}
}

void
entab(int ntws, int tws[], int dtw)
{
	int c, rem, cnt, *ctw;

	ctw = tws;
	rem = *ctw; // chars 'til next stop
	cnt = 0; // blanks since last stop or non-blank
	while((c = getchar()) != EOF) {
		switch(c) {
		case '\n':
			for(; cnt > 0; --cnt)
				if(putchar(' ') == EOF)
					exits("putchar");
			if(putchar(c) == EOF)
				exits("putchar");
			ctw = tws;
			rem = *ctw;
			break;
		case ' ':
			++cnt;
			--rem;
			break;
		case '\t':
			if(putchar(c) == EOF)
				exits("putchar");
			cnt = 0;
			rem = 0;
			break;
		default:
			for(; cnt > 0; --cnt)
				if(putchar(' ') == EOF)
					exits("putchar");
			if(putchar(c) == EOF)
				exits("putchar");
			--rem;
			break;
		}
		if(rem == 0) {
			if(cnt > 0) {
				if(putchar('\t') == EOF)
					exits("putchar");
				cnt = 0;
			}
			if(ctw != &dtw && ctw - tws < ntws)
				ctw++;
			else
				ctw = &dtw;
			rem = *ctw;
		}
	}
}
