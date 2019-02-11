package greedy

//import "fmt"

/**
 * the activity selection problem takes a list of
 * activities, each with a start and end time
 * [{s_1, f_1}, ..., {s_n, f_n}], s_i < f_i
 * ordered by end times f_1 < ... < f_n
 * and asks for a subsequence of maximum length
 * [{s_{i_1}, f_{i_1}}, ..., {s_{i_m}, f_{i_m}}]
 * (i.e. maximum number of activities) such that
 * no two activities occur at the same time,
 * i.e. f_{i_j} <= s_{i_{j+1}} for j=1,...,m-1
 */
type Act struct {
	Start int
	End int
}

type Acts []Act

/* there is a dynamic programming solution to this
 * problem where, if an optimal solution contains
 * an activity {s_k, f_k}, there are subproblems
 * consisting of activity that end before s_k and
 * start after f_k.
 *
 * we define these subproblems by subsets S_{i,j}
 * of activities that start after activity i ends
 * and end before activity j starts.
 */
func (acts Acts) DynSel() ([][]int, [][]int) {
	acts = append(Acts{Act{0, 0}}, acts...)
	acts_end := acts[len(acts)-1].End
	acts = append(acts, Act{acts_end, acts_end})
	m := make([][]int, 0)
	s := make([][]int, 0)
	for i := 0; i < len(acts); i++ {
		m = append(m, make([]int, len(acts)))
		s = append(s, make([]int, len(acts)))
	}
	for l := 1; l < len(acts); l++ {
		for i := 0; i < len(acts) - l; i++ {
			j := i + l
			for k := i + 1; k < j; k++ {
				if acts[k].Start >= acts[i].End &&
						 acts[k].End <= acts[j].Start {
					mm := m[i][k] + m[k][j] + 1
					if mm > m[i][j] {
						m[i][j] = mm
						s[i][j] = k
					}
				}
			}
		}
	}
	return m, s
}

func ActDynSelSol(s [][]int, lo, hi int) []int {
	ai := s[lo][hi]
	if ai == 0 {
		return make([]int, 0)
	}
	before := ActDynSelSol(s, lo, ai)
	after := ActDynSelSol(s, ai, hi)
	sol := append(before, ai)
	return append(sol, after...)
}

/* "greedy" algorithms solve optimization problems
 * without computing solutions to subproblems.
 * the "greedy choice" here is to immediately select 
 * the activity with the earliest finish time.
 * for any optimal solution to the activity problem,
 * removing the activity with the earliest finish
 * time from the solution set and substituting the
 * activity with the earliest finish time overall
 * yields another optimal solution:  the activity
 * with the earliest finish time is always part of
 * *some* optimal solution.
 *
 * so from the standpoint of analysis, greedy
 * algorithms are similar to dynamic programming
 * in that we need to ensure that making a greedy
 * choice (1) is optimal and (2) results in a smaller
 * subproblem that can also be solved by making a
 * a greedy choice.  in this case, the subproblem
 * consists of the activities that start after the
 * chosen activity finishes.
 */
func GSelAux(in Acts, sel map[Act]bool) {
	if len(in) == 0 {
		return
	}
	act_one := in[0]
	var rem Acts
	for _, act := range in {
		if act.Start >= act_one.End {
			rem = append(rem, act)
		}
	}
	sel[act_one] = true
	GSelAux(rem, sel)
}

func (acts Acts) GSel() map[Act]bool {
	sol := make(map[Act]bool)
	GSelAux(acts, sol)
	return sol
}

func (acts Acts) GISel() map[Act]bool {
	sol := make(map[Act]bool)
	c := 0
	sol[acts[c]] = true
	for idx, act := range acts[1:] {
		if act.Start >= acts[c].End {
			c = idx + 1
			sol[acts[c]] = true
		}
	}
	return sol
}

/**
 * huffman codes are a method of data compression.
 * specifically, a string is can be represented by
 * a binary prefix code, an encoding of each character
 * in binary such that no character's sequence of
 * bits is a prefix of any other character's sequence.
 * binary prefix codes can be represented as full
 * binary trees (i.e. trees where every non-leaf
 * node has two children):  the tree's leaves are
 * the characters, the tree's left and right edges
 * are labellel 0 and 1, respectively, and a 
 * character's prefix code is the sequence of edge
 * labels from the root of the tree to its leaf.
 *
 * if a string has characters c_1,...,c_n with
 * frequencies (number of occurrences of each char
 * within the string) f_1,..., f_n, then a prefix
 * code that uses b_i bits for character c_i takes
 * b_1*f_1 * ... * b_n*f_n bits to encode the entire
 * string.  huffman codes are a methodology to create
 * binary prefix codes that minimizes this number
 * of bits for a given string (i.e. sequence of
 * frequences).
 *
 * proof of the algorithm's correctness (that the
 * greedy choice is part of an optimal solution,
 * and that the resulting subproblem of constructing
 * a prefix code on n-1 characters corresponding
 * to the greedy choice in the original problem
 * yields an optimal solution to the original)
 * is involved but straightforward.  the greedy
 * choice yielding an optimal solution follows
 * from the observation that leaves with minimum
 * frequency can be swapped with leaves of maximum
 * depth without increasing a prefix code's cost.
 * optimal substructure follows from contradiction:
 * /any/ optimal solution to the original problem,
 * with cost M can be related to the cost of the
 * subproblem M' by M' = M + C for some constant C.
 * so if the subproblem doesn't result in an optimal
 * solution to the original, then the optimal
 * solution to the original contradicts optimality
 * of the subproblem.
 *
 * todo: more detailed (typeset) notes
 */
type HNode struct {
	Left *HNode
	Right *HNode
	Char rune
	Freq int
}

/* the implementation needs a min-priority queue.
 * see heapsort.
 */
type HHeap []HNode

func (a *HHeap) MinHeapify(i int) {
	l := i * 2 + 1
	r := i * 2 + 2
	sm := i
	if l < len(*a) && (*a)[l].Freq < (*a)[sm].Freq {
		sm = l
	}
	if r < len(*a) && (*a)[r].Freq < (*a)[sm].Freq {
		sm = r
	}
	if sm != i {
		tmp := (*a)[i]
		(*a)[i] = (*a)[sm]
		(*a)[sm] = tmp
		a.MinHeapify(sm)
	}
}

func (a *HHeap) ExtractMin() (HNode, bool) {
	if len(*a) < 1 {
		return HNode{}, false
	}
	min := (*a)[0]
	(*a)[0] = (*a)[len(*a)-1]
	*a = (*a)[:len(*a)-1]
	a.MinHeapify(0)
	return min, true
}

func (a *HHeap) DecreaseKey(i int, x int) {
	if x > (*a)[i].Freq {
		panic("value not a decrease")
	}
	(*a)[i].Freq = x
	for i > 0 {
		p := (i - 1) / 2
		ph := (*a)[p]
		ih := (*a)[i]
		if ph.Freq <= ih.Freq {
			break
		}
		(*a)[i] = ph
		(*a)[p] = ih
		i = p
	}
}

func (a *HHeap) MinInsert(h HNode) {
	*a = append(*a, h)
	i := len(*a) - 1
	inf := h.Freq + 1
	if pk := (*a)[(i - 1)/2].Freq + 1; pk > inf {
		inf = pk
	}
	okey := h.Freq
	h.Freq = inf
	a.DecreaseKey(i, okey)
}


func Huffman(chars []HNode) HNode {
	qalloc := HHeap(make([]HNode, 0))
	q := &qalloc
	for _, char := range chars {
		q.MinInsert(char)
	}
	for i := 0; i < len(chars) - 1; i++ {
		hn := HNode{}
		x, ok := q.ExtractMin()
		if !ok {
			panic("no node")
		}
		y, ok := q.ExtractMin()
		if !ok {
			panic("no node")
		}
		hn.Left = &x
		hn.Right = &y
		ksum := x.Freq + y.Freq
		hn.Freq = ksum
		q.MinInsert(hn)
	}
	return (*q)[0]
}

/* todo: encode and decode strings to and from
 *   byte sequences using huffman trees.
 *
 * recall that the binary sequence might not be
 * divisible by 8, so use one byte to describe
 * the offset.
 */

