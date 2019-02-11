package dynamic

import "fmt"

/**
 * the "rod cutting" problem consists of two inputs:
 * - a list of prices for rods of integer lengths
 * - an integer length of a rod
 * the output of the problem is the maximum price
 * that can be obtained by cutting the rod into
 * integer length pieces -- and optionally the
 * places the rod need be cut in order to obtain
 * that price.
 */

type RodPrices []int

/* we can solve the problem using a divide-and-conquer
 * method by realizing that the max price can be
 * obtained by making no cuts or by starting with
 * the cut that obtains the maximum price closest
 * to one side of the rod.  then, if further cuts
 * are required, the cuts made on the other side
 * of the first cut must maximize the price of the
 * remaining length of rod, or otherwise they wouldn't
 * maximize the price of the original rod.
 *
 * this recursive version demonstrates the essential
 * reasoning described above.  it is *not* a dynamic
 * programming algorithm.
 */

func (p RodPrices) CutRodRecursive(n int) int {
	if n == 0 {
		return 0
	}
	var r int
	q := p[n]
	for i := 1; i < n; i++ {
		r = p.CutRodRecursive(i)
		q = Max(q, r + p[n-i])
	}
	return q
}

func Max(x, y int) int {
	if x < y {
		return y
	}
	return x
}

/* the performance issue here and the reason this is
 * not dynamic programming is that the one call to
 * `CutRodRecursive` will cause multiple recursive
 * calls /with the same parameters/
 *
             3
        /    |    \
       2     1     0
    /  | \   |
   2   1  0  0
 / |   |
1  0   0
|
0
*
* depicts the recursive calls necessary for an initial
* call with n=3, for instance.  it's a self-similar
* tree with a depth of 3: each level is created by
* making two copies of the current level, one with
* and one without the root node, and making all n+1
* resulting root nodes the child nodes of a new root 
* node to create a tree of depth n+1.
* since the number of nodes doubles for each layer of
* depth, the number of nodes in such a tree is 2^n.
* that is, this algorithm runs in exponential time.
*
* one way to avoid the recursive calls is memoization.
* this is still not dynamic programming, although
* it is just about as performant.  it modifies the
* existing recursive algorithm to store results
* after they've been computed, avoiding traversing
* the self-similarities in the above tree.
*/

func cutRodMemoizedH(p RodPrices,
			n int, memp []int) int {
	if n == 0 {
		return 0
	}
	if memo := memp[n]; memo >= 0 {
//		print("got the memo\n")
		return memo
	}
	var r int
	q := p[n]
	for i := 1; i < n; i++ {
		r = cutRodMemoizedH(p, i, memp)
		q = Max(q, r + p[n-i])
	}
	memp[n] = q
	return q

}

func (p RodPrices) CutRodMemoized(n int) int {
	memp := make([]int, n + 1)
	for idx, _ := range memp {
		memp[idx] = -1
	}
	return cutRodMemoizedH(p, n, memp)
}

/* the dynamic programming approach here is to make
 * filling in the memoization data structure, `memp`,
 * the central focus rather than viewing the data
 * structure as an add-on to a recursive approach.
 * indeed "programming" in the phrase dynamic 
 * programming refers to a data structure as in
 * the program of events at a conference, not
 * programming as in writing code:  the focus
 * is on updating a data structure based on
 * the current values in that data structure.
 */

func (p RodPrices) CutRodDP(n int) int {
	mp := make([]int, n + 1)
	mp[0] = 0
	var q, r int
	for m := 1; m <= n; m++ {
		q = p[m]
		for i := 1; i < m; i++ {
			r = mp[i]
			q = Max(q, r + p[m-i])
		}
		mp[m] = q
	}
	return mp[n]
}

/* we can additionally maintain a slice with
 * the data about the length of cuts required
 * to obtain the the maximum price
 */
func (p RodPrices) CutRodDPSol(n int) ([]int, []int) {
	mp := make([]int, n + 1)
	fc := make([]int, n + 1)
	mp[0] = 0
	var q, r, s int
	for m := 1; m <= n; m++ {
		q = p[m]
		fc[m] = m
		for i := 1; i < m; i++ {
			r = mp[i]
			s = r + p[m-i]
			if s > q {
				q = s
				fc[m] = i
			}
		}
		mp[m] = q
	}
	return mp, fc
}

/* here's maintaining solution data with the
 * memoized version
 * todo: cleanup this impl, removing excess vars, etc.
 */

func cutRodMemoSolH(p RodPrices, n int,
		memp []int, mefc [][]int) (int, []int) {
	if n == 0 {
		return 0, make([]int, 0)
	}
	if memo := memp[n]; memo >= 0 {
		return memo, mefc[n]
	}
	var r, s int
	var sol, rsol []int
	q := p[n]
	fc := n
	sol = make([]int, 0)
	for i := 1; i < n; i++ {
		r, rsol = cutRodMemoSolH(
				p, i, memp, mefc)
		s = r + p[n-i]
		if s > q {
			q = s
			fc = n-i
			sol = rsol
		}
	}
	memp[n] = q
	sol = append(sol, fc)
	mefc[n] = sol
	return q, sol
}

func (p RodPrices) CutRodMemoSol(n int) (int, []int) {
	memp := make([]int, n + 1)
	mefc := make([][]int, n + 1)
	for idx, _ := range memp {
		memp[idx] = -1
	}
	return cutRodMemoSolH(p, n, memp, mefc)
}

/* this is an alternate approach described in the
 * text, based on the notion of "density".
 * it doesn't yield correct results and is included
 * as an example of such.
 */
func (p RodPrices) GreedyCut(n int) int {
	calc_dens := func(m int) float64 {
		return float64(m)/float64(p[m])
	}
	var md, cd float64
	var mdlen int
	mdlen = n
	md = calc_dens(n)
	for m := 1; m < n; m++ {
		cd = calc_dens(m)
		if cd > md {
			mdlen = m
			md = cd
		}
	}
	if mdlen == n {
		return p[n]
	} else {
		return p[mdlen] + p.GreedyCut(n-mdlen)
	}
}

/* consider now a variation on the problem
 * wherein each cut incurs some fixed cost,
 * so the profit made from the rod is the
 * sum of the prices minus the cost of the cuts
 */

type RodPricesFC struct {
	Prices []int
	Cost int
}

func (pfc RodPricesFC) CutRodRecursive(n int) int {
	p := pfc.Prices
	c := pfc.Cost
	if n == 0 {
		return 0
	}
	var r int
	q := p[n]
	for i := 1; i < n; i++ {
		r = pfc.CutRodRecursive(i)
		q = Max(q, r + p[n-i] - c)
	}
	return q
}

func (pfc RodPricesFC) CutRodDP(n int) int {
	p := pfc.Prices
	c := pfc.Cost
	mp := make([]int, n + 1)
	mp[0] = 0
	var q, r int
	for m := 1; m <= n; m++ {
		q = p[m]
		for i := 1; i < m; i++ {
			r = mp[i]
			q = Max(q, r + p[m-i] - c)
		}
		mp[m] = q
	}
	return mp[n]
}

/**
 * the matrix-chain multiplication problem is
 * about parenthesizing matrices, not actually
 * performing multiplication:  scalar multiplication
 * is a costly computation in relation to addition
 * and all other operations involved in computing
 * the product of two matrices.
 *
 * this problem is to determine, given a sequence
 * of matrices, the order to compute pairwise
 * products in such that the pqr scalar multiplications
 * required for every two matrices of dimensions 
 * p by q and q by r is minimized over all
 * P(n) = \sum_{k=1}^{n-1} P(k)P(n-k) ~= 2^n
 * possible ways to compute the n-1 pairwise products
 * required for the (associative) product of all
 * matrices in the sequence.
 *
 * since the number of scalar multiplications is
 * dependent on the matrices dimension only, and
 * since the number of rows in each matrix must be
 * equal to the number of columns in the previous
 * matrix (if any), the input to the problem is a
 * sequence of dimensions d_0, ..., d_n
 * corresponding to a product of matrices A_1...A_n
 * such that A_i is a i - 1 by i matrix
 */

type MDims []int

/* as suggested by the above recursive calculation
 * of the number of ways to parenthesize the matrices,
 * and because the outermost parens in an optimal
 * parethesization must contain optimal 
 * parenthesizations of their subsequences in order
 * not to contradict optimality of the original
 * parethezation, a recursive calculation of the
 * number of scalar multiplications required in
 * an optimal parethezation looks like
 m[i,j] = min_{i<=k<j} {m[i,k]+m[k+1,j]+p_{i-1}p_kp_j}
 * where m[i,j] is the number of multiplications
 * required for an optimal parenthezation (one that
 * minimizes scalar multiplications) of matrices
 * A_i..A_j
 *
 * in the dynamic programming approach, we make
 * the tabular data m[i,j] central to the 
 * implementation, and focus on filling in the dynamic
 * program of m[i,j] values.  meanwhile, we keep track
 * of s[i,j], the index k=i,...,j-1 of the
 * parenthezation of A_i..A_j in order to reconstruct
 * an optimal solution rather that just compute
 * the number of multiplications in such a solution
 */
func (p MDims) ChainOrder() ([][]int, [][]int) {
	m := make([][]int, 0)
	s := make([][]int, 0)
	for i := 0; i < len(p); i++ {
		m = append(m, make([]int, len(p)))
		s = append(s, make([]int, len(p)))
	}
	for l := 2; l <= len(p) - 1; l++ {
		for i := 1; i <= len(p) - l; i++ {
			j := i + l - 1 /* at most len(d) - 1 */
			s[i][j] = i
			m[i][j] = m[i][i] + m[i+1][j] +
						p[i-1]*p[i]*p[j]
			for k := i + 1; k < j; k++ {
				mm := m[i][k] + m[k+1][j] +
						p[i-1]*p[k]*p[j]
				if mm < m[i][j] {
					m[i][j] = mm
					s[i][j] = k
				}
			}
		}
	}
	return m, s
}

/* here are some helpers for extracting an optimal
 * solution from the indices stored in s
 */
// todo: reconsider the linguistics here..
//   looking for something more like a union type,
//   which according to the faq
//  https://golang.org/doc/faq#variant_types
//   is properly implemented with an interface
type MParens struct {
	Left *MParens
	Right *MParens
	Idx int
}

func MakeMParens(s [][]int, i, j int) *MParens {
	if i == j {
			return &MParens{Idx: i}
	}
	k := s[i][j]
	return &MParens{
		Left: MakeMParens(s, i, k),
		Right: MakeMParens(s, k + 1, j),
	}
}

func (mp *MParens) String() string {
	if mp.Idx != 0 {
		return fmt.Sprintf("%d", mp.Idx)
	}
	return fmt.Sprintf("(%v%v)", mp.Left, mp.Right)
}

/* as with rod-cutting, the matrix chain multiplication
 * problem admits an inefficient recursive solution
 */
func (p MDims) chainCostAux(i, j int) int {
	if i == j {
		return 0
	}
	var mm int
	m := p.chainCostAux(i + 1, j) +
			p[i-1]*p[i]*p[j]
	for k := i; k < j; k++ {
		mm = p.chainCostAux(i, k) +
				p.chainCostAux(k+1,j) +
				p[i-1]*p[k]*p[j]
		if mm < m {
			m = mm
		}
	}
	return m
}

func (p MDims) ChainCost() int {
	return p.chainCostAux(1, len(p) - 1)
}

/* and the the recursive solution can be memoized
 * as usual
 */
func (p MDims) chainCostAuxMemo(memo [][]int, i, j int) int {
	if i == j {
		return 0
	}
	if mem := memo[i][j]; mem != 0 {
		return mem
	}
	var mm int
	m := p.chainCostAuxMemo(memo, i + 1, j) +
			p[i-1]*p[i]*p[j]
	for k := i; k < j; k++ {
		mm = p.chainCostAuxMemo(memo, i, k) +
				p.chainCostAuxMemo(memo, k+1,j) +
				p[i-1]*p[k]*p[j]
		if mm < m {
			m = mm
		}
	}
	memo[i][j] = m
	return m
}

func (p MDims) ChainCostMemo() int {
	memo := make([][]int, 0)
	for i := 0; i < len(p); i++ {
		memo = append(memo, make([]int, len(p)))
	}
	return p.chainCostAuxMemo(memo, 1, len(p) - 1)
}

/**
 * the Longest Common Sequence (LCS) problem is,
 * given two sequences X = (x_1,..., x_n) and
 * Y = (y_1, ..., y_m), to the longest sequence
 * Z = (z_1, ..., z_k) such that Z is a subsequence
 * of both X and Y.
 * we find optimal substructure in this problem
 * by considering the cases x_n == y_m and otherwise:
 * if x_n == y_m, then x_n == y_m == z_k since
 * any Z that doesn't acknowledge the last element
 * of X and Y can be made longer by including this
 * element.  otherwise, in the case x_n != y_m,
 * we cannot have z_k == x_n && z_k == y_m, so
 * the LCS of X, Y must be the LCS of either
 * X_{n-1} = (x_1,..., x_{n-1}) or Y_{n-1}.
 *
 * as with the matrix chain multiplication problem,
 * we'll fill in a program (in the sense of a table)
 * with both the value being optimized (length of
 * the LCS) as well as information about how to
 * navigate from a problem to its optimal subproblems.
 */

const (
		XA = 1
		YA = 2
		XYA = 3
)

func LCS(x, y []rune) ([][]int, [][]int) {
	m := make([][]int, 0)
	s := make([][]int, 0)
	for i := 0; i < len(x) + 1; i++ {
		m = append(m, make([]int, len(y) + 1))
		s = append(s, make([]int, len(y) + 1))
	}
	for i := 1; i < len(x) + 1; i++ {
		for j := 1; j < len(y) + 1; j++ {
			switch {
			case x[i-1] == y[j-1]:
				s[i][j] = XYA
				m[i][j] = m[i-1][j-1] + 1
			case m[i-1][j] < m[i][j-1]:
				s[i][j] = YA
				m[i][j] = m[i][j-1]
			default:
				s[i][j] = XA
				m[i][j] = m[i-1][j]
			}
		}
	}
	return m, s
}

/* reconstruct the optimal solution.
 * todo: use m, the table of lengths, to reconstruct
 */
func LCSsols(x, y []rune, s[][]int) []rune {
	rsol := make([]rune, 0)
	i := len(s) - 1
	j := len(s[0]) - 1
	for i > 0 && j > 0 {
		switch s[i][j] {
		case XYA:
			rsol = append(rsol, x[i-1])
			i--
			j--
		case XA:
			i--
		case YA:
			j--
		default:
			panic(fmt.Sprintf("unknown s %v", s[i][j]))
		}
	}
	sol := make([]rune, 0)
	for k := len(rsol) - 1; k >= 0; k-- {
		sol = append(sol, rsol[k])
	}
	return sol
}

/** todo: optimal binary search trees */

