package bintree

/* binary search trees */

/// definition

type Tree struct {
	Left *Tree
	Key int
	Right *Tree
	P *Tree
}

func (t *Tree) InOrderWalk() []int {
	if t == nil {
		return make([]int, 0)
	}
	left := t.Left.InOrderWalk()
	right := t.Right.InOrderWalk()
	sorted_keys := make([]int, 0)
	sorted_keys = append(sorted_keys, left...)
	sorted_keys = append(sorted_keys, t.Key)
	sorted_keys = append(sorted_keys, right...)
	return sorted_keys
}

func (t *Tree) PreOrderWalk() []int {
	if t == nil {
		return make([]int, 0)
	}
	left := t.Left.PreOrderWalk()
	right := t.Right.PreOrderWalk()
	sorted_keys := make([]int, 0)
	sorted_keys = append(sorted_keys, t.Key)
	sorted_keys = append(sorted_keys, left...)
	sorted_keys = append(sorted_keys, right...)
	return sorted_keys
}

func (t *Tree) PostOrderWalk() []int {
	if t == nil {
		return make([]int, 0)
	}
	left := t.Left.PostOrderWalk()
	right := t.Right.PostOrderWalk()
	sorted_keys := make([]int, 0)
	sorted_keys = append(sorted_keys, left...)
	sorted_keys = append(sorted_keys, right...)
	sorted_keys = append(sorted_keys, t.Key)
	return sorted_keys
}

/* non-recursive version of previous.  */
func (t *Tree) InOrderWalkStack() []int {
	stack := make([]*Tree, 0)
	var sl int
	var popped *Tree
	sk := make([]int, 0)
	for t != nil || len(stack) != 0 {
		for t != nil {
			stack = append(stack, t)
			t = t.Left
		}
		sl = len(stack)
		popped = stack[sl-1]
		stack = stack[:sl-1]
		sk = append(sk, popped.Key)
		t = popped.Right
	}
	return sk
}

func (t *Tree) InOrderWalkSuccessor() []int {
	sk := make([]int, 0)
	t = t.Min()
	for t != nil {
		sk = append(sk, t.Key)
		t = t.Successor()
	}
	return sk
}

/* todo:
https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
https://en.wikipedia.org/wiki/Threaded_binary_tree
*/

/// queries

func TreeSearch(t *Tree, k int) *Tree {
	if t == nil || k == t.Key {
		return t
	}
	if k < t.Key {
		return TreeSearch(t.Left, k)
	}
	return TreeSearch(t.Right, k)
}

func (t *Tree) Search(k int) *Tree {
	for t != nil && t.Key != k {
		if k < t.Key {
			t = t.Left
		} else {
			t = t.Right
		}
	}
	return t
}

func (t *Tree) Min() *Tree {
	for t.Left != nil {
		t = t.Left
	}
	return t
}

func (t *Tree) Max() *Tree {
	for t.Right != nil {
		t = t.Right
	}
	return t
}

func (t *Tree) MinR() *Tree {
	l := t.Left
	if l == nil {
		return t
	}
	return l.MinR()
}

func (t *Tree) MaxR() *Tree {
	r := t.Right
	if r == nil {
		return t
	}
	return r.MaxR()
}

/* in the case that node has a right child,
 * suppose its successor is not in its right subtree.
 * then either the node and its successor's nearest
 * common ancestor (possibly the successor itself)
 * has the node in its right subtree, contradicting
 * that the successor is greater than the node,
 * or it has the node in its left subtree, 
 * contradicting minimality of the successor
 * since the node's right subtree contains values
 * both greater than the node and less than its
 * successor.
 *
 * so when a node has right child,
 * its successor is in its right subtree.
 */
func (t *Tree) Successor() *Tree {
	if t.Right != nil {
		return t.Right.Min()
	}
	/* now, for any s > t, the nearest
	 * common ancestor of s and t,
	 * possibly s itself but not t,
	 * has u in its left subtree.
	 *
	 * hence, the successor to t is
	 * the first ancestor that has t in its
	 * left subtree. all ancestors s' with t in
	 * the right subtree are s' < t
	 */
	s := t.P
	for s != nil && t == s.Right {
		t = s
		s = s.P
	}
	return s
}

/* the predecessor notion is the dual of successor */
func (t *Tree) Predecessor() *Tree {
	if t.Left != nil {
		return t.Left.Max()
	}
	s := t.P
	for s != nil && t == s.Left {
		t = s
		s = s.P
	}
	return s
}

/* given a sequence of keys that might be a search
 * path, the following check ensures that, once a
 * node and its left or right child are added to
 * the search path, all of the following keys are
 * in the correct (left or right branch) of the given
 * node according to the binary search tree property.
 */
type InvalidPathReason struct {
	BranchKey int
	IsLeft bool
	InvalidKey int
}

func ChkSearchPath(ks []int) *InvalidPathReason {
	if len(ks) < 3 {
		return nil
	}
	rres := ChkSearchPath(ks[1:])
	if ks[0] == ks[1] || rres != nil {
		return rres
	}
	isRight := ks[0] < ks[1]
	for _, k := range ks[2:] {
		if isRight {
			if ks[0] > k {
			return &InvalidPathReason{
				BranchKey: ks[0],
				IsLeft: true,
				InvalidKey: k,
			}
			}
		} else {
			if ks[0] < k {
			return &InvalidPathReason{
				BranchKey: ks[0],
				IsLeft: false,
				InvalidKey: k,
			}
			}
		}
	}
	return nil
}

type ErrNotOneNode Tree

func (e ErrNotOneNode) Error() string {
	return "expected tree without children"
}

func (t *Tree) Insert(z *Tree) error {
	if z.Left != nil || z.Right != nil {
		return ErrNotOneNode(*t)
	}
	var y *Tree
	x := t
	for x != nil {
		y = x
		if z.Key < x.Key {
			x = x.Left
		} else {
			x = x.Right
		}
	}
	z.P = y
	if y == nil {
		/* t was empty */
		t = z
	} else if z.Key < y.Key {
		y.Left = z
	} else {
		y.Right = z
	}
	return nil
}

/* place v in u's location within t */
func (t *Tree) Transplant(u *Tree, v *Tree) {
	if u.P == nil {
		/* u is the root of the tree */
		t = v
	} else if u == u.P.Left {
		u.P.Left = v
	} else {
		u.P.Right = v
	}
	if v != nil {
		v.P = u.P
	}
}

/* when deleting a node z that has both children
 * non-nil, two situations arise according to the
 * location of z's successor, y, within z's right
 * subtree:
 * (1) y is the (right) child of z
 *
       q
       |
       z
     /   \
    l     y
         / \
       nil  x
 *
 * so y can be transplanted to z's location
 * and its (necessarily as z's successor) nil
 * left subtree can be replaced with z's left
 *
       q
       |
       y
     /   \
    l     x
 *
 * (2) y is in the left subtree of the right
 *     child of z
 *
         q
         |
         z
       /   \
      /     \
     l       r
            /
           .
         y
       /   \
      nil   x
 *
 * which we handle in two steps, first
 * re-shaping z's right subtree without
 * worrying about y's parent link or z's
 * right link for a moment
 *
        q
        |               y
        z             /   \
       /             nil   r 
      l                   /
                         .
                        x
 *
 * the the same transplant as in the first case
 * fixes up the broken links from the previous step,
 * removing z and filling in y's nil left subtree
 *
       q
       |
       y
     /   \
    l     r 
         /
        .
       x
 *
 */
func (t *Tree) Delete(z *Tree) {
	if z.Left == nil {
		t.Transplant(z, z.Right)
	} else if z.Right == nil {
		t.Transplant(z, z.Left)
	} else {
		y := z.Successor()
		if y.P != z {
			t.Transplant(y, y.Right)
			y.Right = z.Right
			y.Right.P = y
		}
		t.Transplant(z, y)
		y.Left = z.Left
		y.Left.P = y
	}
}

