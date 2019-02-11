package main

import (
	"fmt"
	"strconv"
	"strings"
	"io"
	"os"
	"image"
	"image/color"
	"image/png"
)

/* here, we begin to explore some standard interfaces,
 * that is, inferfaces used by the stardard library.
 *
 * one way a library can use an interface is to implement
 * functions that "look for" types that implement these 
 * interfaces and behave accordingly.
 *
 * todo: figure out how to implement "looking for"
 *	an interface.  type assertions convert interfaces
 *	/to/ concrete types.  this could be something of
 *	the opposite direction.
 */

/* the Stringer interface is one such interface that
 * the standard library looks for
 *
type Stringer interface {
	String() string
}
 *
 * here's a type that implements the interface
 */

type IPAddr [4]byte
type IPv6Addr [6]byte

func (addr IPAddr) String() string {
	return fmt.Sprintf("%d.%d.%d.%d",
		addr[0], addr[1], addr[2], addr[3])
}

/* now standard library functions like those in the
 * `fmt` package can "look for" the Stringer interface
 * and use it if available.
 */
func stringerdemo() {
	addr := IPAddr{1, 2, 3, 4}
	v6addr := IPv6Addr{1, 2, 3, 4, 5, 6}
	fmt.Printf("builtin formatting: %v\nstringer formatting: %v\n",
			v6addr, addr)
}

/* another standard interface is the error interface
 *
type error interface {
	Error() string
}
 *
 * although Go doesn't make use of try .. catch
 * functionality, several functions use a second
 * return value to signal errors.  in addition to
 * error flags as with map lookups and type
 * assertions, the second return value can also be
 * a type implementing the error interface
 */

func errordemo1() {
	i, err := strconv.Atoi("42")
	fmt.Println("Converted integer: ", i)
	i, err = strconv.Atoi("asdf")
	fmt.Printf("conversion error %T %v\n", err, err)
}

/* the OO picture becomes clearer when implementing
 * a custom error type.  the custom error type itself
 * is unadorned data.  implementing method(s) of the
 * `error` is what makes the type usable as an error.
 */

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	/* todo: why does the absence of a type conversion
	 *	to `float64` create an infinite loop?
	 */
	return fmt.Sprintf("cannot Sqrt negative number: %g",
				float64(e))
}

func MySqrt(x float64) (float64, error) {
	if (x < 0) {
		return 0, ErrNegativeSqrt(x)
	}
	z := float64(1)
	zprev := z + 1
	for zprev != z {
		zprev = z
		z -= (z*z - x) / (2 * z)
	}
	return z, nil
}

func errordemo2() {
	fmt.Println(MySqrt(121))
	fmt.Println(MySqrt(-121))
}

/* up next is the `io.Reader` interface.
 *
type Reader interface {
	Read([]byte) (int, error)
}
 */

/* as an aside, although Go doesn't need
 * function declarations (functions are
 * hoisted), interface types' method
 * declarations can optionally use named
 * parameters for documentatation
 */
type MyReader interface {
	Read(bytes_read []byte) (num_bytes int, err error)
}

/* and that pretty much sums up the
 * `io.Reader` inferface:  buffered bytestreams.
 *
 * here's making a bytestream (Reader)
 * out of a string and using the interface
 * directly
 */

func readerdemo1() {
	r := strings.NewReader("Hi, all")
	b := make([]byte, 4)
	for {
		n, err := r.Read(b)
		fmt.Printf("read %d bytes: %v %q\n", n, b[:n], b[:n])
		/* EOF occurs on first read where there's nothing
		 * to put in the buffer, not the first read where
		 * the buffer can't be filled.
		 */
		if err == io.EOF { break }
	}
}

/* here's a reader, made from scratch, that infinitely
 * fills its buffers with the same character.
 *
 * although it's a toy example, there's an indication
 * here that the empty `struct` can be useful in order
 * to provide type information
 */

type RepeaterReader struct{}

func (r RepeaterReader) Read(bytes []byte) (int, error) {
	for idx, _ := range bytes {
		bytes[idx] = 'A'
	}
	return len(bytes), nil
}

func readerdemo2() {
	b := make([]byte, 3, 4)
	r := RepeaterReader{}
	n, _ := r.Read(b)
	fmt.Printf("read %d bytes: %v %q\n", n, b[:n], b[:n])
}

/* and as a final example, here's a pattern for
 * "wrapping" a reader in another reader to provide
 * additional stream-processing.
 * or, more generally, what we're seeing here is
 * the OO "composition over inheritance" trope:
 * the ROT13 [toy] encryption type contains another
 * io.Reader
 */

type rot13reader struct {
	r io.Reader
}

func rot13(b byte) byte {
	switch {
	case b >= 'A' && b <= 'M' || b >= 'a' && b <= 'm':
		return b + 13
	case b >= 'N' && b <= 'Z' || b >= 'n' && b <= 'z':
		return b - 13
	}
	return b
}

func (r13 rot13reader) Read(bytes []byte) (num_bytes int, err error) {
	num_bytes, err = r13.r.Read(bytes)
	for i := 0; i < num_bytes; i++ {
		bytes[i] = rot13(bytes[i])
	}
	return
}

func readerdemo3() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13reader{s}
	/* there's some new standard library usage here */
	io.Copy(os.Stdout, &r)
	fmt.Println()
}

/* the image standard library provides further
 * examples of interfaces.  in particular,
 * the image interface demonstrates reuse of
 * interfaces by composition
 *
type Image interface {
	ColorModel() color.Model
	Bounds() Rectangle
	At(x, y, int) color.Color
}
 *
 * `color.Model` (as well as `color.Color`)
 * is an interface rather than a type.
 * `ColorModel` (unlike `At`) is an
 * unparameterized method.  so we see a possible
 * pattern for "composition over inheritance"
 * with respect to interface reuse:  an interface
 * can include an unparameterized method that
 * returns another interface type.
 *
 * here's an implementation of Image.
 */

/* this particular image implementation isn't backed
 * by persistent data.  so here we see a slighly less
 * toy example of empty structs.
 */
type MyStaticImage struct{}

/* RGBAModel implements the
 *
type Model interface {
	Convert(c Color) Color
}
 *
 * a means of converting any given implementation
 * of the `color.Color` interface into a particular
 * concrete implementation, e.g. to and from greyscale.
 * the Color interface itself implements a single
 * method to return red-green-blue-alpha values
 *
type Color interface {
	RGBA() (r, g, b, a uint32)
}
 *
 * the values returned by RGBA() are pre-multiplied
 * for easier compositing calculations
 * https://en.wikipedia.org/wiki/Alpha_compositing
 * the values stored in the 32-bit field range up to 2^16
 * for less lossy conversions, and the field is double-wide
 * to prevent overflow on compositing-like operations.
 */
func (im MyStaticImage) ColorModel() color.Model {
	return color.RGBAModel
}

const rgba_max = 255 /* no magic */

func (im MyStaticImage) Bounds() image.Rectangle {
	return image.Rect(0, 0, rgba_max, rgba_max)
}

func (im MyStaticImage) At(x, y int) color.Color {
	v := byte((x + y) / 2)
	return color.RGBA{v, v, rgba_max, rgba_max}
}

func imagedemo1() {
	m := MyStaticImage{}
	f, err := os.Create("static_image.png")
	if (err != nil) {
		fmt.Printf("error opening file %v\n", err)
		return
	}
	err = png.Encode(f, m)
	if (err != nil) {
		fmt.Printf("error encoding image %v\n", err)
		return
	}
	err = f.Close()
	if (err != nil) {
		fmt.Printf("error closing file %v\n", err)
		return
	}
}

/* unlike in this example, images are typically backed by
 * persistent data.  one strategy for doing this is
 * described in the blog post at
 * https://blog.golang.org/go-image-package
 */

func main() {
	stringerdemo()
	errordemo1()
	errordemo2()
	readerdemo1()
	readerdemo2()
	readerdemo3()
	imagedemo1()
}

