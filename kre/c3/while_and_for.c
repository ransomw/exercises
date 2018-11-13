for(<expr_1>; <expr_2>; <expr_3>)
	<statement>

is equivalent to

<expr_1>;
while(<expr_2>) {
	<statement>
	<expr_3>;
}

.. except for `continue;`, tbdiscussed

in `for` above, <expr_1>, <expr_2>, or <expr_3>
can be omitted.  when <expr_2> is omitted it's taken as true,
so in particular,

for(;;) {
	<...>
}

is the idiom for a loop that's broken only
by `break;`, `return;`, etc.

----

when to use while or for?

while((c = getchar()) == ' ' ||
	c == '\n' ||
	c == '\t')
	; /* skip whitespace */

has no initialization, so while is preferable

for(i = 0; i < n; i++)
	<...>

has initialization and increment,
so for is preferable --- indeed, this is the
C idiom for processing the first n elements of an array.

----

==the comma operator==

<expr_1>, <expr_2>;

is a single expression, evaluated left-to-right,
and the result type and value are those of <expr_2>

this is useful in for loops that iterate over multiple values

for(i = 0, j = 10; i < j; i++, j--)
	<...>

since the for loop requires single expressions, not statements.

in general, the comma operator is to be used sparingly:
where a statement in braces suffices, use a statement.
don't insist that every statement is an expression
by way of the comma operator.
