package heapsort

/* heapsort is based on a datastructure called a heap.
 * this datastructure is not to be confused with
 * garbage-collected memory implementations' use of
 * the word.
 *
 * a heap is a sequence viewed as a binary tree
 * indices into the array correspond to nodes in
 * the tree as shown in this example
      0
   1     2
  3 4   5
 *
 * that is, elements in the array correspond to nodes
 * in the tree in a left-to-right, top-to-bottom
 * fashion.
 */

type Heap []int
type Node int

func (i Node) Parent() Node {
	return (i - 1) / 2
}

func (i Node) Left() Node {
	return i * 2 + 1
}

func (i Node) Right() Node {
	return i * 2 + 2
}

func (a *Heap) Size() Node {
	return Node(len(*a))
}

func (a *Heap) Get(i Node) int {
	return (*a)[i]
}

func (a *Heap) Set(i Node, x int) {
	(*a)[i] = x
}

func (a *Heap) Resize(x Node) {
	if x >= 0 {
		*a = (*a)[:x]
	} else {
		*a = (*a)[:cap(*a)]
	}
}

/* the max-heap property is that a node is greater
 * than its children.  the following supposes 
 * that the children of a given node have
 * the max-heap property and re-arranges the heap
 * such that the given node also has the max heap
 * property.
 */
func (a *Heap) MaxHeapify(i Node) {
	l := i.Left()
	r := i.Right()
	lg := i /* largest */
	if l < a.Size() && a.Get(l) > a.Get(lg) {
		lg = l
	}
	if r < a.Size() && a.Get(r) > a.Get(lg) {
		lg = r
	}
	if lg != i {
		tmp := a.Get(i)
		a.Set(i, a.Get(lg))
		a.Set(lg, tmp)
		a.MaxHeapify(lg)
	}
}

/* similarly, the min-heap property is that a node
 * is less than its children.
 */
func (a *Heap) MinHeapify(i Node) {
	l := i.Left()
	r := i.Right()
	sm := i
	if l < a.Size() && a.Get(l) < a.Get(sm) {
		sm = l
	}
	if r < a.Size() && a.Get(r) < a.Get(sm) {
		sm = r
	}
	if sm != i {
		tmp := a.Get(i)
		a.Set(i, a.Get(sm))
		a.Set(sm, tmp)
		a.MinHeapify(sm)
	}
}

/* to ensure the max-heap property, it suffices to
 * run MaxHeapify on every node but the leaves in
 * reverse order:  the leaves have the max-heap
 * property, and since a nodes children follow it
 * in the heap, running in reverse order ensures
 * the assumptions of MaxHeapify are satisfied at
 * every node.
 *
 * the time-complexity of this algorithm turns out
 * to be the number of nodes, although the calculation
 * arrives at this estimate by relating the number
 * of nodes to the height of the tree and summing
 * over the time it takes to run MaxHeapify on a
 * node of a given height.
 */
func (a *Heap) BuildMaxHeap() {
	for i := a.Size()/2 - 1; i >= 0; i-- {
		a.MaxHeapify(i)
	}
}

/* this iterative version of MaxHeapify is based
 * on the same observations about leaf nodes
 * as BuildMaxHeap
 */
func (a *Heap) MaxHeapifyIter(i Node) {
	for i < a.Size() / 2 {
		l := i.Left()
		r := i.Right()
		lg := i /* largest */
		if l < a.Size() && a.Get(l) > a.Get(lg) {
			lg = l
		}
		if r < a.Size() && a.Get(r) > a.Get(lg) {
			lg = r
		}
		if lg == i {
			break
		}
		tmp := a.Get(i)
		a.Set(i, a.Get(lg))
		a.Set(lg, tmp)
		i = lg
	}
}

/* heaps can be used to implement sorting */
func (a *Heap) HeapSort() {
	a.BuildMaxHeap()
	for i := a.Size() - 1; i > 0; i-- {
		tmp := a.Get(0) /* largest element */
		a.Set(0, a.Get(i))
		a.Set(i, tmp)
		/* keep the sorted elements in the same
		 * linear memory used to store the heap
		 * with a reference to where the heap
		 * ends and where the sorted elements begin
		 */
		a.Resize(a.Size() - 1)
		/* all nodes except the first have the
		 * max-heap property, so the following
		 * ensures the heap is a max-heap.
		 */
		a.MaxHeapify(0)
	}
	a.Resize(-1)
}

/* quicksort is used more often than heaps for sorting.
 * heaps are more commonly used to implement priority
 * queues, where dequeued elements are the minimum
 * or maximum among the set of elements in the
 * queue.
 *
 * here's dequeing an element from a max-priority
 * queue implemented with a heap.
 */
func (a *Heap) ExtractMax() (int, bool) {
	if a.Size() < 1 {
		return 0, false
	}
	max := a.Get(0)
	a.Set(0, a.Get(a.Size()-1))
	a.Resize(a.Size() - 1)
	/* similar to the call in HeapSort */
	a.MaxHeapify(0)
	return max, true
}

/* the following resets an element's value to
 * a new one, which is assumed to be at least 
 * as large as the element's current value,
 * preserving the max-heap property.
 *
 * it moves the element up the tree in much the
 * same way MaxHeapify moves the element down the
 * tree.
 */
func (a *Heap) IncreaseKey(i Node, x int) {
	if x < a.Get(i) {
		panic("value not an increase")
	}
	a.Set(i, x)
	for i > 0 {
		p := i.Parent()
		pk := a.Get(p)
		ik := a.Get(i)
		if pk >= ik {
			break
		}
		a.Set(i, pk)
		a.Set(p, ik)
		i = p
	}
}

/* to add a new node, add a new leaf at the end
 * of the tree with a value small enough to preserve
 * the max-heap property and smaller than the value
 * to be added, then call IncreaseKey to set the
 * additional node's value to the desired value
 */
func (a *Heap) MaxInsert(x int) {
	*a = append(*a, 0)
	i := a.Size() - 1
	neginf := x - 1
	if pk := a.Get(i.Parent()) - 1; pk < neginf {
		neginf = pk
	}
	a.Set(i, neginf)
	a.IncreaseKey(i, x)
}

/**
 * min-priority queues are similar 
 */
func (a *Heap) ExtractMin() (int, bool) {
	if a.Size() < 1 {
		return 0, false
	}
	min := a.Get(0)
	a.Set(0, a.Get(a.Size()-1))
	a.Resize(a.Size() - 1)
	a.MinHeapify(0)
	return min, true
}

func (a *Heap) DecreaseKey(i Node, x int) {
	if x > a.Get(i) {
		panic("value not a decrease")
	}
	a.Set(i, x)
	for i > 0 {
		p := i.Parent()
		pk := a.Get(p)
		ik := a.Get(i)
		if pk <= ik {
			break
		}
		a.Set(i, pk)
		a.Set(p, ik)
		i = p
	}
}

func (a *Heap) MinInsert(x int) {
	*a = append(*a, 0)
	i := a.Size() - 1
	inf := x + 1
	if pk := a.Get(i.Parent()) + 1; pk > inf {
		inf = pk
	}
	a.Set(i, inf)
	a.DecreaseKey(i, x)
}


