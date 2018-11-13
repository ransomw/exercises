/* the #include preprocessor directive is used to place
 * the contents of a file into the current file before compilation.
 * it can either be used (as in this demo) with "filename"
 * or (as in all other examples thus far) with <filename>.
 * typically, the "filename" form begins a search in the
 * directory of the source file with the #include directive
 * before falling back on the same implementation-defined
 * rule used to lookup files used by the <filename> form.
 *
 * there's a lot of leeway in the preprocessor behavior:
 * filename needn't even strictly refer to a file.
 * the filesystem abstraction isn't baked into C as a language,
 * and the plan9 preprocessor specifics (of which there are
 * a few) aren't covered in these k&r notes.
 *
 * as a matter of program structure, they're used
 * to consolidate definitions and declarations used
 * by multiple source files.
 *
 * exactly how to divide up definitions among header files
 * is a variation the usual cohesion and decoupling motif:
 * it's more difficult to maintain more header files,
 * while ensuring that each source file has precisely the
 * "information it needs" (in terms of definitions and
 * declarations) can make the source files easier to reason
 * about.
 *
 * the only advice mentioned in this section is that
 * "up to some moderate program size, it's probably best
 *  to have one header file containing everything that's shared
 *  between any two [source files]"
 */


#define NUMBER	'0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int);
