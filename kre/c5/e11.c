#include <u.h>
#include <libc.h>
#include <stdio.h>
#define TAB_WIDTH	8
#define MAXSTOPS	10


void detab(int, int *, int);
void entab(int, int *, int);

void
main(int argc, char *argv[])
{
	int isdetab = 0;
	int ntws, tws[MAXSTOPS];
	int i, c;

	while(--argc > 0 && (*++argv)[0] == '-') {
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
	/* todo: pointer arithmetic version */
	for(i = 0; i < argc; i++)
		tws[i] = atoi(argv[i]);
	tws[i] = TAB_WIDTH;
	ntws = argc == 0 ? 1 : argc;

	if(isdetab)
		detab(ntws, tws, TAB_WIDTH);
	else
		entab(ntws, tws, TAB_WIDTH);

	exits(0);
}

/* ntw - number tab widths
 * tws - tab widths
 * dtw - default tab width
 * ctw - current tab width
 */
void
detab(int ntws, int tws[], int dtw)
{
	int c, rem, *ctw;

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
