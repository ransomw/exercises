package dynamic

import "testing"
import (
	"reflect"
)

var prices RodPrices = RodPrices([]int{
	0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,
})

var max_price []int = []int{
	0, 1, 5, 8, 10, 13, 17, 18, 22, 25, 30,
}

var first_cut []int = []int{
	0, 1, 2, 3, 2, 2, 6, 1, 2, 3, 10,
}

func TestCutRodRecursive(t *testing.T) {
	for i := 1; i < len(max_price); i++ {
		mp := max_price[i]
		cp := prices.CutRodRecursive(i)
		if mp != cp {
			t.Errorf("%v != %v (%v)",
					mp, cp, i)
		}
	}
}

func TestCutRodMemoized(t *testing.T) {
	for i := 1; i < len(max_price); i++ {
		mp := max_price[i]
		cp := prices.CutRodMemoized(i)
		if mp != cp {
			t.Errorf("%v != %v (%v)",
					mp, cp, i)
		}
	}
}

func TestCutRodDP(t *testing.T) {
	for i := 1; i < len(max_price); i++ {
		mp := max_price[i]
		cp := prices.CutRodDP(i)
		if mp != cp {
			t.Errorf("%v != %v (%v)",
					mp, cp, i)
		}
	}
}

func TestCutRodDPSol(t *testing.T) {
	mp, fc := prices.CutRodDPSol(len(max_price)-1)
	if !reflect.DeepEqual(mp, max_price) {
		t.Errorf("%v != %v", mp, max_price)
	}
	if !reflect.DeepEqual(fc, first_cut) {
		t.Errorf("%v != %v", fc, first_cut)
	}
}

func TestGreedyCut(t *testing.T) {
	for i := 1; i < len(max_price); i++ {
		cp := prices.CutRodDP(i)
		gcp := prices.GreedyCut(i)
		if cp != gcp {
			t.Logf(
	"done at %d (%d != %d)", i, cp, gcp)
			return
		}
	}
	t.Errorf("didn't find mismatch")
}

func TestRodPricesFC(t *testing.T) {
	pfc := RodPricesFC{
		Prices: []int(prices),
		Cost: 1,
	}
	for i := 1; i < len(pfc.Prices); i++ {
		rsol := pfc.CutRodRecursive(i)
		dsol := pfc.CutRodDP(i)
		if rsol != dsol {
			t.Errorf("%d != %d (%d)",
				rsol, dsol, i)
		}
	}
}

func get_rod_cut_sol(n int) []int {
	sol := make([]int, 0)
	for n > 0 {
		sol = append(sol, first_cut[n])
		n -= first_cut[n]
	}
	return sol
}

func TestCutRodMemoSolOnce(t *testing.T) {
	i := 5
		mp := max_price[i]
		sol := get_rod_cut_sol(i)
		cp, csol := prices.CutRodMemoSol(i)
		if mp != cp {
			t.Errorf("%v != %v (%v)",
					mp, cp, i)
		}
		if !reflect.DeepEqual(sol, csol) {
			t.Errorf("%v != %v (%v)",
					sol, csol, i)
		}
}


func TestCutRodMemoSol(t *testing.T) {
	for i := 1; i < len(max_price); i++ {
		mp := max_price[i]
		sol := get_rod_cut_sol(i)
		cp, csol := prices.CutRodMemoSol(i)
		if mp != cp {
			t.Errorf("%v != %v (%v)",
					mp, cp, i)
		}
		if !reflect.DeepEqual(sol, csol) {
			t.Errorf("%v != %v (%v)",
					sol, csol, i)
		}
	}
}

var matrix_dims []int = []int{
		30, 35, 15, 5, 10, 20, 25}

func TestChainOrder(t *testing.T) {
	mexpected := [][]int {
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 15750, 7875, 9375, 11875, 15125},
		{0, 0, 0, 2625, 4375, 7125, 10500},
		{0, 0, 0, 0, 750, 2500, 5375},
		{0, 0, 0, 0, 0, 1000, 3500},
		{0, 0, 0, 0, 0, 0, 5000},
		{0, 0, 0, 0, 0, 0, 0},
	}
	sexpected := [][]int {
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 3, 3, 3},
		{0, 0, 0, 2, 3, 3, 3},
		{0, 0, 0, 0, 3, 3, 3},
		{0, 0, 0, 0, 0, 4, 5},
		{0, 0, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 0, 0},
	}
	d := MDims(matrix_dims)
	m, s := d.ChainOrder()
	if !reflect.DeepEqual(m, mexpected) {
		t.Errorf("%v != %v", m, mexpected)
	}
	if !reflect.DeepEqual(s, sexpected) {
		t.Errorf("%v != %v", s, sexpected)
	}
	ps := MakeMParens(s, 1, 6).String();
	if ps != "((1(23))((45)6))" {
			t.Errorf("%q not correct", ps)
	}
}

func TestChainCost(t *testing.T) {
	d := MDims(matrix_dims)
	if c := d.ChainCost(); c != 15125 {
		t.Errorf("%v != %v", c, 15125)
	}
}

func TestChainCostMemo(t *testing.T) {
	d := MDims(matrix_dims)
	if c := d.ChainCostMemo(); c != 15125 {
		t.Errorf("%v != %v", c, 15125)
	}
}

func TestLCS(t *testing.T) {
	mexpected := [][]int{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1},
		{0, 1, 1, 1, 1, 2, 2},
		{0, 1, 1, 2, 2, 2, 2},
		{0, 1, 1, 2, 2, 3, 3},
		{0, 1, 2, 2, 2, 3, 3},
		{0, 1, 2, 2, 3, 3, 4},
		{0, 1, 2, 2, 3, 4, 4},
	}
	sexpected := [][]int{
		{0, 0, 0, 0, 0, 0, 0},
		{0, XA, XA, XA, XYA, YA, XYA},
		{0, XYA, YA, YA, XA, XYA, YA},
		{0, XA, XA, XYA, YA, XA, XA},
		{0, XYA, XA, XA, XA, XYA, YA},
		{0, XA, XYA, XA, XA, XA, XA},
		{0, XA, XA, XA, XYA, XA, XYA},
		{0, XYA, XA, XA, XA, XYA, XA},
	}
	X := []rune{'A', 'B', 'C', 'B', 'D', 'A', 'B'}
	Y := []rune{'B', 'D', 'C', 'A', 'B', 'A'}
	m, s := LCS(X, Y)
	if !reflect.DeepEqual(m, mexpected) {
		t.Errorf("%v != %v", m, mexpected)
		t.Logf("%v", m)
		t.Logf("%v", mexpected)
	}
	if !reflect.DeepEqual(s, sexpected) {
		t.Errorf("%v != %v", s, sexpected)
		t.Logf("%v", s)
		t.Logf("%v", sexpected)
	}
	Se := []rune{'B', 'C', 'B', 'A'}
	Ss := LCSsols(X, Y, s)
	if !reflect.DeepEqual(Ss, Se) {
		t.Errorf("%v != %v", Ss, Se)
	}
}

