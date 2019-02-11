package main

import (
	"fmt"
	"time"
	"runtime"
//	"math"
)

/* control flow statements in Go omit parens
 * on the conditional and require curly braces
 * on the body.
 */
func ifdemo() {
	n := "that"
	if true {
		fmt.Println("hi")
	} else {
		fmt.Println("there")
	}
	/* `if` statements can initialize
	 * local variables.
	 */
	if n := "you"; false {
		fmt.Println("world")
	} else {
		fmt.Println(n)
	}
	fmt.Println(n)
}

/* `for` is the only looping construct in Go.
 */
func fordemo () {
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)
	sum = 1 // not a short assignment b/c there's
		// nothing to redeclare
	/* init and post statements are optional */
	for ; sum < 12; {
		sum += sum
	}
	fmt.Println(sum)
	sum = 1
	/* and the semicolon can be omitted when init and post
	 * are both absent.
	 * in other words, there's no `while` construct.
	 */
	for sum < 30 {
		sum += sum
	}
	fmt.Println(sum)
	/* for infinite loops,
	for {
		// forever
	}
	*/
	/* as an aside, one technique to show that 
	 * the babylonian method converges is to
	 * use a theorem from the dynamical systems
	 * theory regarding stable attractive fixed
	 * points.
	 */
	babylon := func (x float64) float64 {
		z := float64(1)
		zprev := z + 1
		for zprev != z {
			zprev = z
			z -= (z*z - x) / (2 * z)
		}
		return z
	}
	fmt.Println(babylon(121))
	/* btw, there is a `break` statement as in C
	 */
	for i := 0; i < 5; i++ {
		if i == 3 {
			fmt.Println("breaking")
			break
		}
		if i > 3 {
			fmt.Println("broken break")
		}
	}
}

/* `switch` doesn't need `break`s!
 */
func switchdemo() {
	/* also, it can have local variables like `if` */
	switch today := time.Now().Weekday(); time.Saturday {
	case today + 0:
		fmt.Println("today")
	case today + 1:
		fmt.Println("tomorrow")
	case today + 6:
		fmt.Println("it's Sunday, you dolt")
	default:
		fmt.Println("later")
	}
	sanity := func () string {
		fmt.Println("check")
		return "9"
	}
	my_os := runtime.GOOS
	/* `case` conditions are evaluated in order.
	 * if an earlier case is run, later conditions
	 * aren't evaluated.
	 */
	switch my_os {
	case "linux":
		fmt.Println("put on your tux")
	case "freebsd":
		fmt.Println("throw the horns")
		/* break does still exist, however */
		break
		fmt.Println("broken break")
	case sanity():
		fmt.Println("we learned!")
	default:
		fmt.Printf("still running %s\n", my_os)
	}
	/* switch without a condition is sugar for
	 * `switch true`, an effective idiom for
	 * if-else chains
	 */
	now := time.Now()
	switch {
	case now.Hour() < 12:
		fmt.Println("moin")
	case now.Hour() < 17:
		fmt.Println("afternoon")
	default:
		fmt.Println("evening")
	}
}

/* `defer` replaces goto for cleanup and error-handling
 * tasks.  it works by delaying a function call until
 * just after its enclosing function returns.
 *
 * multiple `defer`s are pushed onto a stack and popped
 * in the reverse order when the function returns.
 *
 * also, in the case of named return values, the deferred
 * functions can modify the enclosing function's return value.
 */
func defera () (rv int) {
	for i := 0; i < 3; i++ {
		defer fmt.Print(i)
	}
	defer func() { rv++; }()
	return 27
}

func deferdemo() {
	fmt.Println(defera())
}

func main () {
	ifdemo()
	fordemo()
	switchdemo()
	deferdemo()
}
