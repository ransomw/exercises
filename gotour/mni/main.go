package main

import (
	"fmt"
	"math"
)

/* `type` in Go differs from `typedef` in C
 * insomuch as Go has a notion of "methods"
 * in the OO sense.
 *
 * methods are declared on types (or pointers
 * to types) declared in the same package as
 * the method.  a package that does not contain
 * a type's definition cannot define methods
 * on that type, so in particular, methods
 * can't be declared on basic types.
 */
type Vertex struct {
	X, Y float64
}

/* methods are defined as functions with a
 * special "receiver" argument
 */
func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

/* this function does the same thing as the
 * previous method
 */
func AbsFunc(v Vertex) float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

/* and here's a version of the same method 
 * that takes a pointer as a receiver argument
 */
func (v *Vertex) AbsP() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

/* and here's a method with a pointer receiver
 * that modifies the value referenced by the
 * pointer.
 */
func (v *Vertex) ScaleP(a float64) {
	v.X *= a
	v.Y *= a
}

func methodsdemo1() {
	v1 := Vertex{3, 4}
	v1p := &v1
	/* methods differ from function calls
	 * in that types and pointers to types are
	 * referenced and dereferenced according to
	 * the reciever type.
	 */
	fmt.Println(v1.Abs(), AbsFunc(v1), /*here*/ v1.AbsP())
	fmt.Println(/* and here */ v1p.Abs(), v1p.AbsP())
	/* whereas this would be a build error */
//	AbsFunc(v1p)
	/* ... and just to demo that the pointer
	 * receiver method indeed modifies the value.
	 * with or without the method call's coercion
	 */
	fmt.Println(v1)
	v1.ScaleP(5)
	fmt.Println(v1)
	v1p.ScaleP(0.4)
	fmt.Println(v1)
}

/* were methods the only language construct
 * to consider, the only factors to consider
 * when deciding to pass pointers or values
 * as methods' receivers would be
 * - whether the method needs to modify the
 *   attached value (of course)
 * - possible perf concerns about time to
 *   allocate memory for method calls outweighing
 *   the understood advantages of pass by
 *   value
 *
 * the other language construct that's worth
 * considering when deciding to pass pointer
 * receivers or not is the `interface` type.
 * let's have a look-see..
 */

/* `interface` is a type like `struct`, `Map`,
 * `Array`, or `func` and pointers for that matter.
 * it (an interface) consists of a few named
 * method definitions, sans receiver type.
 *
 * so this is an interface with one method.
 */
type I interface {
	M()
}

/* now here are a few types */
type T struct {
	S string
}

type MyFloat float64

type MyInt int64

/* ... the named method implemented
 * for a couple of those types ...
 */
func (t T) M() {
	fmt.Println(t.S)
}

func (x *MyFloat) M() {
	if (x != nil) {
		y := *x + 11
		fmt.Println(y)
	} else {
		fmt.Println("M got nil")
	}
}

/* ... and now the method names are enough to
 * dynamically glue concrete types to `interface`
 * values.
 */
func interfacedemo1() {
	var i I /* here's the interface value */
	var i2 I
	var someInt MyInt = 1
	var someFloat MyFloat = MyFloat(someInt) + 0.23
	var floatPtr *MyFloat
	/* and it can have concrete types according
	 * to the method receivers
	 */
	i = T{"Hi"}
	i.M()
	i = &someFloat
	i.M()
	/* it cannot have types that don't have the
	 * necessary method(s) defined.  the following
	 * is a build error.
	 */
//	i = someInt
	/* similarly, and perhaps unexpectedly given
	 * that coercion that can occur when calling
	 * a method on a concrete type, the following
	 * is also illegal:  Go will not allow
	 * concrete types that disagree with method
	 * receiver types.
	 */
//	i = someFloat
	/* by the way, note the difference between
	 * a nil interface value and an interface
	 * value that has a concrete type with nil
	 * as an underlying value.
	 */
	fmt.Printf("%v, %T\n", i2, i2)
	/* this is an error because without a concrete
	 * type, there's no method to be resolved.
	 */
//	i2.M()
	i2 = floatPtr
	fmt.Printf("%v, %T\n", i2, i2)
	/* writing pointer receivers to handle nil
	 * values is good practice.
	 */
	i2.M()
}

/* so the rule of thumb is to either use pointer
 * receivers or not for all methods of any concrete
 * type.  that way, an interface can be defined
 * by choosing any or all of the available methods
 * and not create any ambiguity when assigning a
 * concrete type to an interface.
 *
 * tbd: what variety of coercion or polymorphism
 *	would be necessary to allow assigning
 *	both pointers and non-pointers to the
 *	same interface.  and what possible use-case
 *	would such functionality have.
 */

/* note that the empty interface (the interface
 * with no methods) is a valid interface definition.
 * rather than an edge case included for consistency
 * like empty `struct`s, empty interfaces are
 * a language feature that can be used much like
 * void pointers in C
 */

type EmtpyStruct struct{} // not all that useful

func interfacedemo2() {
	var i interface{} // frequently used
	/* the empty interface can hold any type */
	i = "hiya"
	/* and then "type assertions" can be used to
	 * recover the underlying concrete type
	 */
	s := i.(string)
	/* much like reading value out of a map,
	 * type assertions can also return a
	 * status flag
	 */
	s, ok := i.(string)
	fmt.Println(s, ok)
	/* like reading from a map, zero values
	 * are used when the underlying concrete type
	 * isn't the one specified in the assertion
	 */
	f, ok := i.(float64)
	fmt.Println(f, ok)
	/* unlike reading from a map, using the
	 * one return value form of a type assertion
	 * results in an error when the correct type
	 * is not supplied, hence the name "assertion"
	 */
//	f = i.(float64)
	/* type switches are another way to
	 * extract the underlying concrete value
	 * from an interface type
	 */
	switch v := i.(type) {
	case int:
		fmt.Println("got an int", v)
	case string:
		fmt.Println("got a string", v)
	default:
		fmt.Printf("got some other type %T, %v\n", v, v)
	}
}

func main() {
	methodsdemo1()
	interfacedemo1()
	interfacedemo2()
}

