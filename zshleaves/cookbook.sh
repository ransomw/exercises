#! /usr/bin/env zsh

### ZLE

### Substitutions

# split string
# .. by newlines
my_string='asdf
qwer'
lines=(${(f)ms})
# .. according to shell parameter parsing
my_string='-xv -f ar.tar'
args=(${(z)my_string})
