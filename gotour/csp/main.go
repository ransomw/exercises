package main

import (
	"fmt"
	"time"
)

/* Go uses Communicating Sequential Processes
 * for parallelism with language features
 * much like Clojure's core.async library.
 */

/* much like Clojure's go macro spins off its
 * body in a new sequential process, Go uses the
 * keyword `go` to spin off any given function call
 * in a new sequental process, called a "goroutine"
 *
 * "goroutines" are *not* coroutines.  they're
 * separate flows of control, and the caller cannot
 * await a goroutine after spinning one off.
 */
func sleepnsay() {
	fmt.Println("sleeping")
	time.Sleep(100)
	fmt.Println("world")
}

func goroutinedemo() {
	go sleepnsay()
	fmt.Println("hello")
	time.Sleep(10000)
	fmt.Println("done")
}

/* channels are used to communicate with and
 * between goroutines.  the make() builtin
 * used with slices and maps is used to create
 * channels, and there's a single channel
 * operator `<-` used to send and recv.
 *
 * the second parameter to make() specifies
 * the channel's buffer size, the number of
 * values that can be present in the channel
 * at once.
 */
func chandemo1() {
	c1 := make(chan string, 2)
	c1 <- "hello"
	c1 <- "world"
	/* since the channel's buffer is full by now,
	 * and since there are no goroutines running,
	 * uncommenting the following line causes a
	 * runtime error (deadlock)
	 */
//	c1 <- "also, more things"
	/* note the cap() builtin has semantics
	 * for channels as well as slices
	 */
	fmt.Printf("channel size: %d\n", cap(c1))
	/* values are received from the channel in
	 * the same order that they're sent
	 */
	fmt.Println(<-c1, <-c1)
}

/* when goroutines are running, writing to
 * an unbuffered channel or reading from a channel
 * without any values isn't a runtime error:
 * the `<-` operator will block the current
 * sequential process (goroutine or otherwise)
 * until another sequential process with
 * access to the channel makes use of the `<-`
 * operator with the channel on the opposite side.
 *
 * it's common to use unbuffered channels.
 */

func saytochan(s string, c chan string) {
	c <- s
}

func chandemo2() {
	c := make(chan string)
	go saytochan("hello", c)
	/* since `go` spins off a lightweight thread,
	 * the messages put in the channel by this
	 * goroutine aren't gauranteed to be in any
	 * particular order.
	 * uncommenting the `time.Sleep` calls would
	 * ensure that "hello world" is printed in order
	 */
//	time.Sleep(10000)
	go saytochan("world", c)
//	time.Sleep(10000)
	go saytochan("other", c)
	fmt.Println(<-c, <-c)
	/* in general, there's no need to cleanup
	 * channels.  they'll be garbage collected
	 * at the end of a function that creates them
	 */
	go saytochan("things", c)
}

/* channels can be closed, however.
 * after closing a channel, sending to the channel with `<-`
 * will cause a panic (and hence an error if cleanup
 * functionality isn't registered).
 *
 * the second return value of `<-` recvs,
 * a status flag, is false if
 * - the channel is closed
 * - there are no more values to read from the channel
 */

func chandemo3() {
	c := make(chan int, 1)
	c <- 1
	/* all reads thus far would return ok == true
	 * since we haven't used close()
	 */
	x, ok := <-c
	fmt.Println(x, ok)
	c <- 1
	close(c)
	/* it's still ok to recv from a buffered channel
	 * after it's been closed if the buffer contains
	 * unreceived values
	 */
	x, ok = <-c
	fmt.Println(x, ok)
	x, ok = <-c
	fmt.Println(x, ok)
}

/* again, there's often no need to explicitly close()
 * channels, and when using close(), it's important
 * not to write to closed channels (usually by ensuring
 * that the portion of the program responsible for
 * writing to the channel is the portion that closes it).
 *
 * that said, it's often helpful to close() a channel
 * when using the `for .. range` construct with a channel.
 * the `for .. range` loop will not exit, blocking if
 * necessary, until the channel whose values are being
 * looped over is closed
 */
func chandemo4() {
	c := make(chan int, 2)
	c <- 1
	c <- 2
	close(c)
	for x := range c {
		fmt.Println(x)
	}
}

/* a sockets-like `select` token has similar semantics
 * to Clojure's `async/alt!`.
 *
 * `select` allows a blocking recv from one of several
 * channels or, if the `default` case is present, it
 * allows polling one or more channels.
 */

func polldatanflag(c, flag chan string) string {
	select {
	/* case statements can be any use of `<-`,
	 * either send or recv
	 */
	case x := <-c:
		return x
	/* if multiple operations can occur subject
	 * to blocking conditions, one is chosen at random.
	 *
	 * unlike a `switch` the order or the case statements
	 * in a `select` doesn't matter
	 */
	case <-flag:
		return "flag"
	default:
		return "no data"
	}
}

func selectdemo1() {
	c := make(chan string, 1)
	flag := make(chan string, 1)
	fmt.Println(polldatanflag(c, flag))
	flag <- "something"
	fmt.Println(polldatanflag(c, flag))
	c <- "else"
	fmt.Println(polldatanflag(c, flag))
}

func main() {
	goroutinedemo()
	chandemo1()
	chandemo2()
	chandemo3()
	chandemo4()
	selectdemo1()
}

