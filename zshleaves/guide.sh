#! /usr/bin/env zsh

# print is a builtin shell command
print "'ello, world"

# if, then, else, fi are all commands, too,
# login and interactive are options.
# options can use any case and variable underscores.
if [[ -o login ]]; then
    print "login shell"
else
    print "not a login shell"
fi

if [[ -o inter_ACT_ive ]]; then
    print "interactive shell"
else
    print "not an interactive shell"
fi

# ... and [[ ... ]] is a command, too
[[ 1 = 1 ]]
print "1 == 1 ($?)"
[[ 1 = 2 ]]
print "1 == 2 ($?)"

##

# norcs is set by the -f flag
if [[ -o norcs ]]; then
    print "only /etc/zshenv is run"
else
    print ".zprofile, .zshrc, and .zlogin are run after zshenv"
fi
# ... or actually rcs is.
# 'no' is sugar for options
if [[ ! -o rcs ]]; then
    print "only /etc/zshenv is run"
else
    print ".zprofile, .zshrc, and .zlogin are run after zshenv"
fi

# not all options have flags.
# the shell can set and unset options
setopt login
# or equivalently
set -o login
if [[ -o login ]]; then
    print "login shell"
else
    print "not a login shell"
fi
unsetopt login
if [[ -o login ]]; then
    print "login shell"
else
    print "not a login shell"
fi

##

# parameter/variable assignment is sensitive to spaces
# around the `=` sign
some_param='some val'

# the `--` signals that there are no more flags left,
# so params beginning with a '-' aren't mistaken for flags...
print -- '$some_param is "'$some_param'"'
# ..as usual, note that single quotes are string literals
#  and that string concatentation happens automatically with
#  params to print just as to echo.

# the `--` no-more-flags flag isn't used by all programs
# or builtins, although it is a useful standard to be aware of.

# there are also arrays!  declaring them is similar to rc,
# although the space around the `=` sign thing still applies.
some_arr=(this
          is
          'an array ...')

# indexing into arrays is done with [square brackets]
print -- $some_arr[3] # 'an array...'

# or reverse-lookup can be done with [(r)elem], which returns
# the element, provided it exists in the array.
print -- $some_arr[(r)is]
# this is more commonly used to check for existence of elements
# in an array along with the test `-z` for the empty string.
if [[ -z $some_arr[(r)is] ]]; then
    print -- miss # not in the array
else
    print -- hit # in the array
fi
if [[ -z $some_arr[(r)not] ]]; then
    print -- miss
else
    print -- hit
fi

# prepend and append to arrays with
some_arr=(so $some_arr)
some_arr=($some_arr yeh)
# and count values with $#<name>,
# recalling that in shell langs indices start from 1
print -- $some_arr[1] $some_arr[5] $#some_arr

# and we can slice arrays
print -- $some_arr[1,3] # so this is
print -- $some_arr[3,5] # is an array ... yeh
print -- $some_arr[2,-2] # this is an array ...
# and shift, too, which is not a pop: it doesn't result in a value
print -- $some_arr # so this is an array ... yeh
shift some_arr
print -- $some_arr # this is an array ... yeh
shift some_arr
print -- $some_arr # is an array ... yeh


# everything after the $calar `$` sign used to tokenize input
# that describes a variable can be enclosed in {curly braces}
# to more clearly delineate the variable usage from other
# parts of the shell script
print -- '$some_param is "'${some_param}'"'
print -- ${some_arr[3]}

# one array of particular interest is fpath...
print -- $fpath[1]
# ... scripts in these directories can be run as if they were
#     functions following an `autoload <name>`.

# there are also modifiers that can be applied to variables
print -- $fpath[1]:t $fpath[1]:h
# :t -- tail
# :h -- head
# :r -- remove suffix of file
# :l -- lowercase
# :u -- uppercase
# :s/re/rep/ -- substitute regexp with replacement
# :gs/re/rep/ -- substitute regexp with replacement, global
# :& or :g& -- repeat the last substitution

## prompt percent escapes
# the -P flag to print enables the same percent escapes
# used in (all equivalent) $PS1, $PROMPT, and $prompt.
# here's username@hostname
print -P -- '%n@%m'

# here are a few dates and times..
print -P -- '%t' # 12-hr format
#  3:35AM
print -P -- '%T' # 24-hr format
# 3:35
print -P -- '%*' # 24-hr format with seconds
# 3:35:38
print -P -- '%w' # day of week and month
# Sun 31
print -P -- '%W' # local date
# 03/31/19
print -P -- '%D' # local date, intl
# 19-03-31
# and more generally, it's possible to pass a string to the strftime()
# standard library function with '%D{<strftime_param>}'
print -P -- '%D{%A, %B!}' # strftime(3) formatting
# Sunday, March!

# there's also a ternary operator on the current hour (T)
# or mintues past the hour (t)
print -P -- '%(3T.three : %w.not : %W)'

# there's also this idea of truncating parts of the prompt with
# `%num_chars<<` from the left or `%num_chars>>` from the right
print -P -- '%10<<%W %D{%A, %B}!'
# ay, March!
print -P -- '%10>>%W %D{%A, %B}!'
# 03/31/19 S
# these truncations can also include some characters to indicate
# that the text has been truncated
print -P -- '%10<...<%W %D{%A, %B}!'
# ... March!
print -P -- '%10>...>%W %D{%A, %B}!'
# 03/31/1...
# also, truncation can be turned off with a closing %<< or %>>
print -P -- '%10>...>%W %D{%A, %B}%>>!'
# 03/31/1...!

# truncation is particularly useful for paths
print -P -- '%/' # cwd, abs
print -P -- '%~' # cwd, relative to any named paths
# to register a named path, set a variable `mydirname=/some/dir`,
# followed by `: ~mydirname` or `setopt AUTO_NAME_DIRS`.
# also, a specific number of path components (beginning with the most
# specific) can be specified with either the absolute or relative paths
print -P -- '%1/ %2/ %3~'

## all about variables #

# `typeset` declares variables, either singly or many-at-a-time.
# variable declarations can be combined with initialization.
# without flags, `typeset` declares scalar variables.
typeset some_typeset_var='some val' some_other_typeset_var

print $some_typeset_var

# typeset can of course be omitted from a variable initialization,
# in which case the variable has global scope.
var='Original value'
# speaking of scope, here's the usual POSIX function synatax.
subfn() {
    print $var
    print $some_typeset_var
    print $arr[2]
}
# now we observe that scalars declared with `typeset` are scoped
# within the function they're declared in.  note that the scoping
# is "dynamical" in that `subfn` has access to `fn`'s var.  this is
# in contrast with "syntactic" scoping in C.
fn() {
    print $var
    typeset var='Value in function' # a local
    other_var='value from function' # a global
    print $var
    subfn
}

# try this at home!
fn
print $var ', ' $other_var ', ' $arr[2]

# further ado about `typeset`ting arrays: the following are equivalent:
# declaring a variable as an array
typeset -a some_typeset_arr
# declaring a variable as a scalar and then
# converting to array by assignment
typeset some_other_typeset_arr
some_other_typeset_arr=()

# notice ... well, notice first that it's `whence`, not `which`
#            -m allows searching by patterns
#            -w prints out what's be found in a parsable way
#          there's also -v for human reading and -c to get fn code
whence -wm 'typese*'
# and by now, notice that typeset is both a reserved word (like `if`)
# as well as a builting (like `print`).
# since reserved words take priority, it usually runs as such
# in order to allow things like
typeset some_var=`echo asdf qwer`
print $some_var # asdf qwer
# with the `builtin` precommand modifier (there's similar `command`
# modifier to access things from the `hash` of executables found in
# $path or otherwise placed in the hash of commands to filenames),
# we can get the old behavior
builtin typeset some_var=`echo asdf qwer`
print $some_var # asdf
# wherein the rules of command substitution forced slightly different
# semantics for assignment and initialization.
# whereever `typeset` is a reserved word, initialization (including
# initialization of arrays) appears to function like assignment.

# ... and there are more types than Perl
typeset not_an_integer
typeset -i an_integer
integer also_an_integer

print -- $not_an_integer $an_integer $also_an_integer

typeset -E a_scientific_notation_float
float also_a_scientific_notation_float=10000
typeset -F a_decimal_notation_float=10000

print -- $a_scientific_notation_float \
      $also_a_scientific_notation_float \
      $a_decimal_notation_float

typeset -E another_scientific_notation_float=10.2
print -- $another_scientific_notation_float

# because the shell does arithmetic!  bye-bye `bc`?
let 'an_integer++'
(( an_integer++ ))
# are equivalent, although the latter form
# is preferred to the former, builtin form
print -- $an_integer
# parens stay balanced
(( an_integer += 2 * (++also_an_integer) ))
print -- $an_integer $also_an_integer
# we can substitute the results of rithmetic back into the
# shell in a similar way as the results of subprocesses.
print -- $((1 + 1))

# associative arrays (like in elisp) are a type too,
typeset -A assoc_array=(
    one uno
    two dos
)
assoc_array[three]=tres
print -- $assoc_array[one] $assoc_array[two] # uno dos
# these can behave much like any mapping type
typeset -a keys=(${(k)assoc_array})
# ??? how to inline, removing the `keys` variable?
print -- $keys[2] $keys[1] # two one
print -- ${(v)assoc_array} # uno dos tres
unset 'assoc_array[two]'
print -- ${(kv)assoc_array} # one uno three tres

# there's introspection on type information
print -- ${(t)an_integer} ${(t)assoc_array} # integer association

## in addition to types, variables can have flags
print -- ${(t)PATH} # scalar-export-special

# `typeset` can set these flags as well
typeset -r immutable='read-only'
# immutable='-r' # an error
typeset +r immutable
immutable='-r'
print -- $immutable
# similarly, -x for export, -g for global, and -h for hide
# (the inverse of global)

## finally, `typeset` tie scalars an arrays
# like with $path and $PATH, this occurs so often.
typeset -T tied_scalar tied_array
tied_array=(tide detergent $tied_array)
print -- $tied_scalar # tide:detergent
tied_scalar="bleach:$tied_scalar"
print -- $tied_array[1] # bleach

# double-finally, variables can be deleted with `unset`
print -- $an_integer
unset an_integer
print -- 'nothing' $an_integer

## as far as getting inputs into to the shell goes,
# there's the familiar glob of an argv
print -- $*
# that can then be changed with `set`
whence -vm 'set' # set is a shell builtin
set thing one thing two
print -- $#* ${(t)*} # 4 array-readonly-special

# be careful with `set`, tho, b/c it can also function like `setopt`:
# > set -x
# > set -o xtrace
# > setopt xtrace
# are all equivalent.  and in addition to shell option flags
# and the -o flag to name shell options with the same name as `setopt`,
# `set` has some other flags to change the behavior of this peculiar
# builtin.
set -A an_arr one two
print -- $an_arr ${(t)an_arr} # one two array
# so the upshot is that using the usual -- final flag delineates
# the change to the array of parameters.
set -- -x hat cat
print -- $* # -x hat cat
# ... and this array has all the usual aliases for compatibility
print -- $@[3] $2 $argv[1] # cat hat -x
# `shift` with no array parameter also operates on the parameters
# as usual
shift
print -- $* # cat hat
# ... one neat thing about setting arrays with `set` is references
# ??? equivalent for scalars? (non-eval?)
an_arr_ptr='an_arr'
set -A $an_arr_ptr stuff and things
print -- $an_arr # stuff and things

# the other main way to get user input into the shell is `read`,
# which reads a line-at-a-time
fn read_demo() {
    print -n -- enter some parameter
    read some_param
    print -- ${(t)some_param} # scalar
    print -- 'again:' $some_param
    # using the -A flag causes input to be read as an array
    # with blanks are used as delimiters.
    # compare what happens with muliple consecutive blanks as input
    # with and without the array flag.
    print -n -- enter some _array_ parameter
    read -A arr_param
    print -- ${(t)arr_param} # scalar
    print -- 'again'"$#arr_param"':' $arr_param
    # there's a shortcut instead of these `print -n`s:
    # the '?' delimits the prompt
    read some_param'?prompt>'
    # and flags include an option to read a char at a time
    print -n -- enter some char
    read -k some_char_param
    print -- 'again:' $some_char_param
    # or to distingish 'Y' and 'y' from other characters.
    # this always reads the character 'y' or 'n'.  it also
    # has a correspondingly appropriate return code.
    print -n -- enter Y/n
    read -q some_bool_param
    ret=$?
    print
    print -- 'again (translated):' $some_bool_param '('$ret')'
    # as with rc, there's an Input File Separator variable.
    # presumably, this configures several things in the shell.
    # here, we'll observe that it configures the character(s)
    # that arrays split on
    print -- ${(t)IFS} # scalar-special
    IFS=':' read -A arr_param'?IFS=:>'
    print -- $arr_param
}
# ... there are yet other flags for `read`, and another builtin
#     called `vared` that allows editing more than a line-at-a-time

# !!! uncomment to try it out
# read_demo

## job control
# "job" is a term for subprocesses _or_ commands, functions, etc.
# being run in the shell.

# the terminal doesn't report interrupts (C-c), suspends (C-z), etc.
# to the shell as ascii characters.  instead, it maps control characters
# to control functionality and sends the particular function to the
# shell.
# all this goes to explain that `stty` is an external (POSIX standard)
# program that can be used what keystrokes are used to for job control
# and similar functionality.  run `stty -a` to see.  in fact,
# read stty(1) to get an idea of what a terminal looks like to the OS.
whence -v ttyctl # ttyctl is a shell builtin
# ..and this shell-specific command can be used to either prevent
# subprocesses from changing terminal settings, `ttyctl -f`
# (f for freeze), or allow, `ttyctl -u` (u for unfreeze).

sleep 2 &
sleep 2 &
last_sleep_pid=$!
jobs # [1]  - running    sleep 2
     # [2]  + running    sleep 2
disown %1
# now the shell doesn't know about the last sleep
jobs # [2]  + running    sleep 2
# it's still there in the os, though
ps -e |grep $last_sleep_pid
# and it's possible disown processes right from the start.
# indeed, referencing jobs by %<num>, %+, %- usually isn't done
# from scripts.
# ??? difference between `&!` and `&|`?
sleep 1 &|
sleep 1 &!
jobs # [2]  + running    sleep 2

# the shell can wait on processes in the std C lib sense, either by
# pid or job identifier, provided the process is a subprocess of the
# current shell.
sleep 1 &
last_sleep_pid=$!
print -- 'sleep in background'
wait $last_sleep_pid
print -- 'sleep done'
# waiting prevents zombies, those processes that don't have
# a parent process (other than pid 1) waiting around for them.


whence -v kill
# kill is a shell builtin
# ... as with `print` (instead of `echo`), this is another instance
#   of the shell subsuming utility programs, except this time, the
#   name has not been changed to protect the innocent executable.
#
# in addition to `kill -<num>`, zsh can run `kill -<name>`,
# where <name> is one of the following
print -- $signals
# EXIT HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE ALRM
# TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM PROF WINCH
# INFO USR1 USR2 THR LIBRT ZERR DEBUG
# these are system-specific (from freebsd), except for a few
# zsh-specific signals sent to the shell by the shell
# - EXIT - function exit, shell exit
# - ZERR - command has non-zero exit status
# - DEBUG - sent on every command

# there are two flavors of signal handlers
fn trap_demo() {
    trap 'echo eval flavor' INT
    read '?press ^C, then return>'
    # unregister the handler
    trap - INT
    read '?press ^C or return>'
    TRAPINT() {
        echo 'fn flavor'
    }
    # the function flavor means that /TRAP.*/ isn't a good name
    # for functions that aren't meant as handlers
    read '?press ^C, then return>'
    trap - INT
    read '?press ^C or return>'
    # the function handler flavor is unique b/c it can indicate
    # that the signal hasn't been handled after all and return
    # an updated signal
    TRAPINT() {
        echo 'unhandled exit code'
        return 128
    }
    print -- 'press ^C then `echo $?`'
    read
}

# !!! uncomment to try it out
# trap_demo

# both forms handle signals sent to the shell process only.
# other programs running in the terminal handle signals in their
# own way, no matter what signals the shell is trapping.
# nonetheless,
# "the shell is able to tell that the command got that particular signal"
# because signals like ^C are sent to process *groups*,
# not individual process, and foreground subprocesses are in the same
# group as the shell.
trap_demo_2() {
    TRAPINT() {
        echo 'cat in the box'
    }
    read '?press ^C then return'
    print -- 'press ^C then `echo $?`'
    cat
}
# `cat` (and hence this script) exit with status 130=128+SIGINT.
# adding 128 to the signal number is a standard exit code convention.

# !!! uncomment to try it out
# trap_demo_2

# then try setting some echo trap in the interactive shell,
# and both `trap_demo_2` as well as interrupting the following
# cat
# ... when trap_demo_2 traps the interrupt, the handler in the
#   interactive shell doesn't get called.  otherwise, it does.
# ??? so signals aren't 'broadcast' to process groups?
#     like, if a process handles a signal, other processes
#     in the group don't see it?  where's the freebsd documentation
#     on this stuff?

# when writing functions, handling SIGEXIT is similar to
# golang's `defer`.
# it's always reset after the function exits.
#
# passing variables from a function to an enclosing function
# is an example of s'th the eval trap flavor can do that
# the function trap flavor cannot.  the eval trap's string parameter
# runs in the context that exists after the function exits.
#
# when not making use of the enclosing context,
# standardize on the function trap flavor.
inner_fn() {
    integer innermost=1
    (( innermost++ ))
    trap "typeset trapped_param=$innermost" EXIT
    (( innermost++ ))
    print -- $innermost
}
trap_demo_3() {
    inner_fn
    print -- $trapped_param
}
trap_demo_3
print -- "'$trapped_param'"

# the shell provides a facility to set limits
limit |grep stacksize
# on its processes' resources.
# ??? corresponding OS primities in bsd and linux?

# there's also a way to get some profiling information
whence -v time
# time is a reserved word
time ls &> /dev/null
# ls &> /dev/null  0.00s user 0.00s system 93% cpu 0.001 total
# ... while `times` lists the a grid of <time>s according to
#  the following table
#             |  user space | sys calls
# shell       |    <time>   |  <time>
# subprocesses|    <time>   |  <time>

## exit, return, break, continue and source
# `exit` calls stdlib C function for the shell's process
# `return` exits a function (or a script, but not an interactive shell)
# with a status code.
rvfn() {
    return 'sth'
    print -- nothin
}
rvfn
print -- $? # 0
rvfn() {
    return 2
    print -- nothin
}
rvfn
print -- $? # 2

# break, continue (for loops), and source as usual

whence -v eval # eval is a shell builtin
# `eval` divigations omitted.  it's the same as everywhere:
# give it a string, and it runs it as statements in the current
# context.  with the shell, it concatenates parameters using spaces.

whence -v exec # exec is a shell builtin
# .. what we'd expect from stdlib C:  replaces the shell process
# with the process resulting from the command that it modifies

whence -v noglob # noglob is a shell builtin
noglob print * # *

## more comparisons
# the usual infix operators, including <, > are all string comparisons.
# and == and = are synonyms.  typically, = and != are the only such
# operators used.
# the rhs can be a pattern instead of a string
if [[ asdf = as* ]]; then
    print -- yup
fi

# numeric comparisons within the usual [[ ... ]] comparison
# expression are done with `-<name>`
if [[ 2 -gt 1 ]]
   # other <name>s are
   # 1 -lt 2 && 1 -eq 1 && 1 -le l && l -le 2 && 1 -ge 1
then
    print -- jup
fi
# arithmetic operations give exit status according to whether they
# evaluatue to zero:  evaluating to zero means a not-ok exit of 1.
(( 1 + 27 ))
print $? # 0
(( an_integer = 27 ))
print $? # 0
(( 27 - 20 - 7 ))
print $? # 1
(( an_integer = 0 ))
print $? # 1
(( 0 ))
print $? # 1
# so arithmetic operations can be used to perform comparisons
# on numbers without the quirky infix operators
if (( an_integer < 1 )); then
    print -- indeed
fi

# ... there are a few quirky infix operators used to compare files:
# for [[ file1 -<name> file2 ]] the <names> are
# - ot : older than
# - nt : newer than
# - ef : equivalent file.  tests links created with `ln`

# then there are the unary prefix tests
if [[ -z '' ]]; then
    print -- 'zero-length string'
fi
if [[ -n 'asdf' ]]; then
    print -- 'non-zero-length string'
fi
# including several of the [[ -<name> file ]] form:
# - e : exists
# - f : exists and is regular (e.g. not a directory)
# - x : executable
# as well as the [[ -o <option> ]] test above
# and [[ -t <file_descriptor> ]] to see if the file descriptor is
# attached to a terminal.  (the shell only has 0-9 as file descriptors,
# not arbitrary integers like stdlib C).
if [[ -t 0 ]]; then
    print -- terminal input
else
    print -- 'did you `echo sth |me`?'
fi

# aside from these, there's only logical operators
# &&, ||, ! and parethezation.
if [[ 2 -gt 1 && 1 -lt 2 && 1 -eq 1 && 1 -le 1 && 1 -le 2 && 1 -ge 1 ]]
then
    print -- kup
fi

## options
whence -v getopt
# is a program, not part of the shell proper
whence -v getopts
# is a builtin, similar to `getopt`.

print ${(t)OPTIND} # integer-special
# special b/c this variable is set to 1 at the beginning of
# every script or function.

# here's the guide's example, more or less verbatim
testopts() {
    typeset opt
    # the flags parameter is similar to `getopt`'s:
    # a concatenation of single letters, each followed
    # by an optional `:` to indicate that the named flag takes
    # a parameter.
    while getopts ab: opt; do
        case $opt in
            ('a')
                print -- 'Option a set'
                ;;
            ('b')
                print -- 'Option b set to' $OPTARG
                ;;
            # returned by getopt when it encounters a parameter it
            # not specified in the flags parameter.
            ('?')
                print Bad option, but it\'s ok.
                return # in the sense that this is zero
                ;;
        esac
    done
    # `getopts` advances `$OPTIND` past
    # every parameter it parses, leaving $* unchanged.
    # so the following line is usually added after the `getopts`
    # loop to discard parsed parameters.
    (( OPTIND > 1 )) && shift $(( OPTIND - 1 ))
    print Remaining arguments are: $*
}

# `getopts` is `--`-aware
testopts -b foo -- -a args
# notice that getopts prints its own message about bad options
testopts -q

testopts_02() {
    typeset opt
    # prepending a `:` to the flags parameter silences
    # getopts message about bad options.
    while getopts :a opt; do
        case $opt in
            ('a')
                print -- 'Option a set'
                ;;
            ('?')
                print Bad option, but it\'s ok.
                return
                ;;
        esac
    done
}

testopts_02 -a
testopts_02 -q

##

command umask
# is a thing on most systems, yet
whence -v umask # umask is a shell builtin
# is included with zsh just in case.
# both correspond to a stdlib C call to update a bitmask
# corresponding to the process (and in the case of zsh,
# its subprocesses such as `touch` as well).  this bitmask
# is used by other stdlib C functions and syscalls,
# and the upshot is that it describes permission bits that _aren't_
# set by default when creating a file or directory.

##

# since $* is an array in zsh and we typically keep SH_WORD_SPLIT unset,
# there the main difference between $* and usual "$@" metaphor for
# passing along arguments is whether blank items are removed
# from the array
print_args() {
    print -- '('"$#"')' $*
}
set some '' thing
# with $*, blanks are removed.  with "$@", they aren't.
print_args $* # (2) some thing
print_args "$@" # (3) some thing
# ... so "$@" is still the preferred way to ensure that commands
# get exactly the same parameters that were passed to a script or
# function.
# and in case it's ever necessary to glob all parameters into
# scalar,
print_args "$*" # (1) some thing

# incidentally, there's a syntax to do word splitting
# on a case-by-case basis where it's useful
set 'some thing'
print_args $* # (1) some thing
print_args ${=*} # (2) some thing
# the ${=<name>} syntax isn't specific to parameters
mv='asdf qwer'
ma=(${=mv})
print -- ${(t)mv} ${(t)ma} # scalar array
print -- $ma[2] $ma[1] # qwer asdf

## process substitution

# in addition to inlining the output of a subshell with $(...),
# it's possible to use the output as if it were a file.
grep -n asd <(echo asdf) # 1:asdf
grep -n asd =(echo asdf) # 1:asdf
# the difference between these two is that
# the =(...) form allows seeking through a file on disk,
# whereas the <(...) form must read the file sequentially.

# similarly, >(...) runs a command in a subshell as well.
# here, the command's process's stdin is whatever would be written
# to a file where >(...) is.
echo stuff > >(sed 's/tuff/luff/') # sluff
# is the usual example, although not particularly useful
# (since pipes could do the same thing in this case).

## redirection

# y'know how it's typical to send stderr to stdout with 2>&1?
# what happens here is a two-step close and dup(2) of stderr.
# if the dup file descriptor is omitted, all that happens is
# that the first file descriptor is closed.
echo asdf | cat 1>&- || echo yep
# also, 2>&1 and 2<&1 are typically equivalent.  doesn't matter
# which direction the arrow goes with the close and dup.

# the output of multiple commands can be grouped to a single redirect
{echo -n stuff; echo things} | sed 's/t/s/g' # ssuffshings

# and while bash only has here documents, zsh has here strings as well
sed 's/a/the/' <<<'a thing' # the thing

# todo: say more about redirection, give examples


### ZLE

print
print 'all keymaps'
bindkey -l
print
