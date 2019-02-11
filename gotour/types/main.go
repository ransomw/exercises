package main

import (
	"fmt"
	"strings"
)

/* Go has pointers.  it does /not/ have
 * pointer arithmetic.  otherwise, semantics
 * are what we'd expect from C.
 */
func incptr(intptr *int) {
	/* *T is a pointer containing the
	 * memory addr of a value of type T
	 */
	*intptr++
}

func ptrdemo() {
	i, j := 42, 13
	p := &i
	fmt.Printf("i (via p) = %d\n", *p)
	*p = 21
	fmt.Printf("i = %d\n", i)
	incptr(p)
	fmt.Printf("i = %d\n", i)

	p = &j
	*p += 2
	fmt.Printf("j = %d\n", j)

	/* as in C, there are `nil` semantics
	 * for uninitialized pointers
	 */
	var ptr *int
	if (ptr == nil) {
		fmt.Println("ptr is nil")
	}
	/* unlike C, however, `nil` is a type
	 * defined by the language, not a value
	 * set in the standard library headers
	 */
	fmt.Printf("%T nil type\n", nil)
	fmt.Printf("%d nil as int\n", nil)
}

/* the `type` token is a lot like typedef.
 * it's not explicitly mentioned by the tour,
 * but here's a placeholder demo, recalling
 * builtin floating-point types always
 * have an explicit width
 */
type Float float64

func typedemo() {
	var pislice Float = 3.14
	fmt.Printf("%g (%T)\n", pislice, pislice)
}

/* `struct`s are also a lot like C */
type Vertex struct {
	X int
	Y int
}

type NamedVertex struct {
	/* just as with `var` declarations,
	 * only one type is necessary for
	 * multiple fields of the same type
	 */
	X, Y int
	name string
}

func structdemo() {
	/* since it's idomatic to use type
	 * inference, structs literals always
	 * begin with the struct type
	 */
	var v0 Vertex = Vertex{0, 1}
	v1 := Vertex{1, 2}
	/* when initializing structs,
	 * it's permissible to specify fields
	 * by name.  when naming fields,
	 * order isn't important, and unnamed
	 * fields get initial values according
	 * to intital values for their component
	 * basic types
	 */
	v2 := Vertex{Y: 11}
	/* as in C, structs can be initialized by assignment,
	 * and the `.` member operator accesses fields
	 */
	v2c := v2
	v2c.Y = 9
	nv := NamedVertex{name: "mine"}
	nvp := &nv
	/* in Go, unlike C, struct pointer fields
	 * are accessed with the same syntax as
	 * struct fields:  there's no `.`/`->` divide
	 */
	nv.X = 27
	nvp.Y = 13

	fmt.Println(v0, v1, v2, v2c, nv)
}

/* aside from left-to-right type definition syntax
 * and absence of pointer arithmetic, arrays
 * are much like arrays in C.
 *
 * "the absence of pointer" arithmetic is a notable
 * difference:  names of arrays reference the entire
 * array.  they aren't pointers to the first element
 * of an array.  arrays of different sizes are different
 * types, and assigment initializes these types just
 * like assigment of structs, not by reference passing
 * as in C.
 */

type Line [2]Vertex

func arraydemo() {
	var arr [2]string
	arr[0] = "hi"
	arr[1] = "ya"

	fmt.Println(arr[1], arr[0])

	/* array literals are in curly braces */
	primes := [6]int{2, 3, 5, 7, 11, 13}
	/* writing `...` instead of an array size when
	 * declaring an array literal allows the compiler
	 * to infer the array size.
	 */
	otherprimes := [...]int{17, 19, 29, 31, 41, 43}
	fmt.Println(primes)
	fmt.Println(otherprimes)
	/* note the difference in array assigment
	 * from C.  the following initializes and
	 * modifies a copy of the original array.
	 */
	notprimes := primes
	notprimes[0] = 1
	fmt.Println(primes)
	fmt.Println(notprimes)


	/* arrays of structs need precisly one
	 * type definition when declaring a literal.
	 * the struct type can be supplied in the literal,
	 * but it's optional.
	 */
	theline := Line{{0, 0}, Vertex{Y: 2, X: 1}}
	fmt.Println(theline)
}

/* in practice, Go programs use _slices_
 * more often than arrays.
 *
 * the mental model of a slice consists of
 * - a pointer /into/ an array
 * - the number of elements in the
 *   array the slice has access to
 *   (the slice's length)
 * - the number of elements between the
 *   pointer and the end of the array
 *   (the slice's capacity)
 *
 * slices are the only way to get pointers
 * to indexes inside an array, and data
 * structures like slices are how languages
 * like Python implement dynamically-sized
 * arrays under the hood.
 * so Go is choosing some middle ground
 * between pointer arithmetic in C and
 * dynamic arrays in Python.
 */

/* []T is the type of a slice with elements
 * of type T
 */
func printSlice(s []string) {
	fmt.Printf("len=%d cap=%d %v\n",
	/* the builtins `len` and `cap` are
	 * used to access a slice's length
	 * and capacity
	 */
			len(s), cap(s), s)
}

func slicedemo() {
	names := [...]string{
		"john",
		"paul",
		"george",
		"ringo",
	}
	/* the `arr[lo:hi]` notation creates
	 * a slice from an array
	 */
	printSlice(names[1:3])
	printSlice(names[2:])
	printSlice(names[:])
	/* slice literals can be used to
	 * initialize an underlying array
	 * and a slice into it all at once
	 */
	printSlice([]string{"john", "miles", "paul", "art"})

	/* now check out what happens when slicing a 
	 * slice.  these first slices successively
	 * narrow the slice
	 */
	ns := names[:] // fresh slice
	printSlice(ns)
	ns = ns[1:] // move pointer, update len and cap
	ns = ns[:2] // update len
	printSlice(ns)
	ns = ns[1:]
	printSlice(ns)
	/* now the slice has len = 1, cap = 2,
	 * so it's possible to widen the slice
	 */
	ns = ns[:2] // move pointer, update len and cap
	printSlice(ns) // update len
	/* be careful not to attempt to widen a slice
	 * beyond its capacity, tho.  the following
	 * is a runtime error
	 */
//	printSlice(ns[:3])

	/* as with pointers,
	 * declaring a slice without an initializer
	 * results in a `nil` value
	 */
	 var is []int
	 fmt.Printf("len=%d cap=%d %v\n", len(is), cap(is), is)
	 if (is == nil) {
		 fmt.Println("yep, we have nils")
	 }
}

/* like Java and Python, Go provides
 * a builtin hashmapping type, `map`
 */

func mapdemo() {
	/* a map of strings to vertices */
	var vm map[string]Vertex
	if (vm == nil) {
		fmt.Println("maps also init to nil")
	}
	/* consider the semantics of map literals
	 * by comparison to struct literals:
	 * since maps don't have pre-defined fields,
	 * keys are required.
	 *
	 * in the following example, also note that,
	 * as with arrays of Vertex types, specifying
	 * the Vertex struct type is optional.
	 */
	vm = map[string]Vertex{
		"Bell Labs": {40, -74},
		"Google": Vertex{37, -122},
	}
	fmt.Println(vm)
	/* maps' entries can be inserted or updated
	 * using a syntax similar to Python's dictionaries
	 */
	vm["Bell Labs"] = Vertex{41, -74}
	vm["Santana Row"] = Vertex{37, -122}
	fmt.Println(vm)
	/* retrieving an element from a map always
	 * provides a return value along with a status
	 * flag indicating whether the element was
	 * found in the map.
	 */
	var v Vertex
	var ok bool
	v, ok = vm["Bell Labs"]
	fmt.Println(v, ok)
	/* when the element is not found in the map
	 * the return value is the zero value of the
	 * map's value type
	 */
	v, ok = vm["Synaptics"]
	fmt.Println(v, ok)
	/* it's not necessary to check the status flag,
	 * although otherwise, there's no way to distinguish
	 * the presence of a zero value in the map
	 * from an absence of a key in the map
	 */
	v = vm["Synaptics"]
	fmt.Println(v)
	/* there's a builtin, `delete`, to remove elements 
	 * from a map.  `delete` modifies the map in-place;
	 * it does not return a different map.
	 */
	delete(vm, "Bell Labs")
	v, ok = vm["Bell Labs"]
	fmt.Println(v, ok)
}

/* these nil-able types have a few other
 * builtins and language features associated with
 * them.
 */

func builtindemo() {
	printSlice := func(s []int) {
		fmt.Printf("len=%d cap=%d %v\n",
				len(s), cap(s), s)
	}

	/* in Go, we `make` instead of `malloc`-ing.
	 * make() can create both maps and slices.
	 *
	 * there's no `sizeof`-type stuff.  `make`
	 * takes the type directly as a parameter.
	 *
	 * ??? is it possible for user-specified
	 * functions to take types as parameters?
	 *
	 * when `make`-ing a map, the type alone
	 * is sufficient.  to make a slice,
	 * the length and capacity must be
	 * specified
	 */
	mm := make(map[string]int)
	s1 := make([]int, 3) /* len = cap = 3 */
	s2 := make([]int, 3, 5) /* len = 3, cap = 5 */

	mm["answer"] = 42
	fmt.Println(mm)
	printSlice(s1)
	printSlice(s2)
	s2 = s2[:4]
	printSlice(s2)

	/* note that there's a difference
	 * between a nil slice and a slice
	 * of length zero .. explicit nil
	 * checks are the only way to distinguish
	 * so far
	 */
	s3 := make([]int, 0)
	printSlice(s3)
	if (s3 == nil) {
		// doesn't print
		fmt.Println("made a nil")
	}

	/* `append` is another builtin used
	 * to grow slices.  it might be desirable
	 * to roll custom `append`-like functions
	 * in some situations.  the builtin is
	 * provided for most applications.
	 *
	 * `append` returns a new slice rather than
	 * modifying the existing slice.  there's
	 * no gaurantee about what the new slice's
	 * capacity will be, except that it'll be
	 * sufficient for the appended elements.
	 */
	s4 := append(s3, 2, 3, 5)
	printSlice(s3)
	printSlice(s4)

	/* the `for..range` is more of a linguistic
	 * construct than a builtin.  it can be
	 * used for both slices an maps
	 */
	for idx, val := range s4 {
		fmt.Printf("%d (%d), ", val, idx)
	}
	fmt.Printf("\n")
	mm["question"] = 27
	for key, val := range mm {
		fmt.Println(val, key)
	}
	fmt.Printf("\n")
}

/* unlike arrays, assigment of maps and slices
 * is by reference, not by value
 */
func assignmentdemo() {
	ms := []int{2,3,5}
	msc := ms
	mm := map[string]int {
		"key1": 1,
		"key2": 2,
	}
	mmc := mm
	mmc["key1"] = 11
	msc[1] = 1
	/* each variable references the same
	 * chunk of memory: both the original
	 * and the copy print the same value
	 */
	fmt.Println(ms, msc)
	fmt.Println(mm, mmc)
}

/* similarly, maps an slices are pass by
 * reference to function calls.  
 */
func incslice(is []int) {
	for idx, _ := range is {
		is[idx]++
	}
}

func incmap(im map[string]int) {
	for key, _ := range im {
		im[key]++
	}
}

func passrefdemo() {
	mis := []int{1, 2, 3}
	mim := map[string]int{
		"asdf": 1,
		"qwer": 2,
	}
	incslice(mis)
	fmt.Println(mis)
	incmap(mim)
	fmt.Println(mim)
}

/* make() and a loop or some utility function are
 * the proper way to copy maps' and slices'
 * (aka nil-able types) values in memory.
 */

func main () {
	fmt.Println("heyo")
	ptrdemo()
	typedemo()
	structdemo()
	arraydemo()
	slicedemo()
	mapdemo()
	builtindemo()
	assignmentdemo()
	passrefdemo()
}

/* exercise results */

func Pic(dx, dy int) [][]uint8 {
	var mp [][]uint8
	var cr []uint8
	for y := 0; y < dy; y++ {
		cr = make([]uint8, dx)
		for x, _ := range cr {
			cr[x] = uint8((x + y) / 2)
		}
		mp = append(mp, cr)
	}
	return mp
}


func WordCount(s string) map[string]int {
	var exists bool
	var words []string = strings.Fields(s)
	wc := make(map[string]int)
	for _, word := range words {
		_, exists = wc[word]
		if exists {
			wc[word]++
		} else {
			wc[word] = 1
		}
	}
	return wc
}


func fibonacci() func() int {
	var prev, curr int = 0, 1
	return func() int {
		var next = prev + curr
		var rv = prev
		prev = curr
		curr = next
		return rv
	}
}

