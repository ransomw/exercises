package main

/* package imports can be parenthesized
 * or factored across multiple lines.
 *
 * the package name is the last portion
 * of the path to the package by convention.
 */
import (
	"fmt"
	"math/rand"
)
import "math"
// import "math/cmplx"

/* here's function declaration syntax.
 *
 * unlike C, which uses the same syntax
 * for both declarations /and/ statements
 * (e.g. a[3] is an element of an array
 * and `int a[3]` is a declaration),
 * Go has a separate declaration synatax.
 *
 * in particular, note the type information
 * appears to the right of the variable name.
 * the overall idea is that types read
 * left-to-right (as opposed to the "spiral
 * rule" in C).
 */
func add(x int, y int) int {
	return x + y
}

/* sequences of parameters can be followed
 * by a single type declaration
 */
func subtract(x, y int) int {
	return x - y
}

func funcdemo () {
	fmt.Printf("hello, world\n")
	/* package publics are uppercase */
	fmt.Println("My favorite number is", rand.Intn(10))
	fmt.Printf("Now you have %g problems.\n", math.Sqrt(7))
	fmt.Println(add(42, 13))
	fmt.Println(subtract(42, 13))
}

/* typed variable declarations begin with the
 * `var` token with one type per `var`.
 */
var python, java bool
/* optional initializers can be provided
 * with assignment syntax after the declaration.
 *
 * uninitialized numbers are zero, unitialized
 * strings (yes, strings are a primitive type)
 * are empty, and uninitialized booleans are false.
 * and that covers pretty much all the basic types

bool
string
// types without a width are machine-dependent
int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr
byte // alias for uint8
rune // alias for int32
     // represents a Unicode code point
     // name appropriated from Plan 9's <u.h>
float32 float64
complex64 complex128

*/
var clojure, guile, elisp bool = true, true, false

/* continuing with JS-like tokens, constants
 * are declared with `const`.
 */
const csname string = "filthy mcnasty"

func vardemo() {
	/* types can be inferred on assignment */
	var pislice = 3.14
	/* there's also a "short assigment" operator, `:=`,
	 * that's available inside functions only.
	 * it allows omitting the `var` token and doing
	 * inference all at once.
	 * type declarations aren't allowed with this operator,
	 * and it can only be used with names that
	 * aren't declared in the function's local
	 * scope.
	 *
	 * note the paren placement in the typecast
	 * syntax as well.
	 *
	 * while C might express this as something like
	 int piint = pislice;
	 * Go doesn't allow parameters to assigment
	 * of different types as in
	 var piint int = pislice
	 * the following line is idiomatic, not a toy example.
	 */
	piint := int(pislice)
	fmt.Printf("types %T %T\n", piint, pislice)
	fmt.Println(piint)
	python = true
	fmt.Println("python", python, "java", java,
			"clojure", clojure,
			"guile", guile,
			"elisp", elisp)
	fmt.Println(csname)
	/* numeric constants are values accessible
	 * at compile time.  the same numeric constant
	 * may assume different types, depending on
	 * its use (function call, variable
	 * assigment, etc.) in a runtime context.
	 */
	 const (
		 big = 1 << 100
		 small = big >> 99
	 )
	fmt.Printf("%g\n", float64(big));
	fmt.Printf("types %T\n", small)
}

/* functions can return multiple (aka tuples of)
 * values.  no more pointers-as-return-values!
 */
func swap(a, b string) (string, string) {
	return b, a
}

/* there's also this thing called
 * "named return values"
 * where we let the elements of a function's
 * return tuple have names in the function's
 * declaration.  then, there's a "naked return"
 *
 * language design intent here is
 * that the "named vales and naked return"
 * feature be used for short functions only.
 */
func swapper(a, b string) (x, y string) {
	x = b
	y = a
	return
}

func main() {
	funcdemo()
	vardemo()

	s, t := "hello", "world"
	u, v := "ya", "hi"
	w, x := swap(t, s)
	y, z := swapper(u, v)
	fmt.Printf("%s %s %s%s\n", w, x, y, z)

	/* also, we've got some notions of anonymous,
	 * first-class, and immediate functions.
	 */
	mf := func () string { return "asdf" }
	mof := mf
	func () { fmt.Println(mof()) }()
}

