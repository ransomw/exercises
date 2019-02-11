package heapsort

import "testing"
import (
	"reflect"
)

func TestMaxHeapify(t *testing.T) {
	in := Heap{16, 4, 10, 14, 7, 9, 3, 2, 8, 1}
	eout := Heap{16, 14, 10, 8, 7, 9, 3, 2, 4, 1}
	in.MaxHeapify(1)
	if !reflect.DeepEqual(in, eout) {
		t.Errorf("%v != %v", in, eout)
	}
}

func TestMaxHeapifyIter(t *testing.T) {
	in := Heap{16, 4, 10, 14, 7, 9, 3, 2, 8, 1}
	eout := Heap{16, 14, 10, 8, 7, 9, 3, 2, 4, 1}
	in.MaxHeapifyIter(1)
	if !reflect.DeepEqual(in, eout) {
		t.Errorf("%v != %v", in, eout)
	}
}

func TestBuildMaxHeap(t *testing.T) {
	in := Heap{4, 1, 3, 2, 16, 9, 10, 14, 8, 7}
	eout := Heap{16, 14, 10, 8, 7, 9, 3, 2, 4, 1}
	in.BuildMaxHeap()
	if !reflect.DeepEqual(in, eout) {
		t.Errorf("%v != %v", in, eout)
	}
}

func TestHeapSort(t *testing.T) {
	in := Heap{3, 2, 5, 4, 1}
	eout := Heap{1, 2, 3, 4, 5}
	in.HeapSort()
	if !reflect.DeepEqual(in, eout) {
		t.Errorf("%v != %v", in, eout)
	}
}

func TestMaxQueue(t *testing.T) {
	a := Heap{}
	in := []int{3, 1, 2}
	eout := []int{3, 2, 1}
	out := make([]int, 0)
	for _, x := range in {
		a.MaxInsert(x)
	}
	x, mor := a.ExtractMax()
	for mor {
		out = append(out, x)
		x, mor = a.ExtractMax()
	}
	if !reflect.DeepEqual(out, eout) {
		t.Errorf("%v != %v", out, eout)
	}
}

func TestMinQueue(t *testing.T) {
	a := Heap{}
	in := []int{3, 1, 2}
	eout := []int{1, 2, 3}
	out := make([]int, 0)
	for _, x := range in {
		a.MinInsert(x)
	}
	x, mor := a.ExtractMin()
	for mor {
		out = append(out, x)
		x, mor = a.ExtractMin()
	}
	if !reflect.DeepEqual(out, eout) {
		t.Errorf("%v != %v", out, eout)
	}
}

