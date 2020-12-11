#include <u.h>
#include <libc.h>

/* demonstrate standard-library ARGBEGIN, ARGEND, ARGF() macros */

/* arguments are copied to the stack, an additional memory
 * segment not mentioned in loaded_programs.rc...
 * these (the stack, the text, and the init and uninit data)
 * comprise all memory segments in the virtual addr space of
 * a loaded program.
 *
 * main() is wrapped in another function that calls exits()
 * in case main() does not, and the program beings executing
 * at the wrapper function.
 * exits() is a system call (a call to code in the kernel)
 * that terminates the calling process:  processes are
 * simply a datatype within the kernel.
 */

void
usage(void)
{
	/* argv0 is initialized by ARG* macros */
	fprint(2, "usage %s [-nv] [-d delims] args\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	int nflag = 0;
	int vflag = 0;
	char *delims = "[]";
	int i;

	ARGBEGIN{
	case 'v':
		vflag = 1;
		break;
	case 'n':
		nflag = 1;
		break;
	case 'd':
		delims = ARGF();
		if(delims == nil || strlen(delims) < 2)
			usage();
		break;
	default:
		usage();
	}ARGEND;

	for(i = 0; i < argc; i++)
		if(vflag)
			print("%c%s%c ", 
				delims[0], argv[i], delims[1]);
		else
			print("%s ", argv[i]);
	if(!nflag)
		print("\n");
	exits(nil);
}
