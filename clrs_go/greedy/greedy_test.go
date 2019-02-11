package greedy

import "testing"
import (
	"reflect"
)

var some_acts Acts = Acts{
	{1, 4},
	{3, 5},
	{0, 6},
	{5, 7},
	{3, 9},
	{5, 9},
	{6, 10},
	{8, 11},
	{8, 12},
	{2, 14},
	{12, 16},
}

func TestActDynSel(t *testing.T) {
	m, s := some_acts.DynSel()
	if ml := m[0][len(m) - 1]; ml != 4 {
		t.Errorf("%v != %v", ml, 4)
	}
	sol := ActDynSelSol(s, 0, len(s[0]) - 1)
	sole := []int{1, 4, 8, 11}
	/* 2, 4, 9, 11 is another solution */
	if !reflect.DeepEqual(sol, sole) {
		t.Errorf("%v != %v", sol, sole)
	}
}

func TestActGSel(t *testing.T) {
	sol := some_acts.GSel()
	/* maps with bool values are idomatic
	 * sets in Go
	 */
	sole := map[Act]bool{
		some_acts[0]: true,
		some_acts[3]: true,
		some_acts[7]: true,
		some_acts[10]: true,
	}
	if !reflect.DeepEqual(sol, sole) {
		t.Errorf("%v != %v", sol, sole)
	}
}

func TestActGISel(t *testing.T) {
	sol := some_acts.GISel()
	/* maps with bool values are idomatic
	 * sets in Go
	 */
	sole := map[Act]bool{
		some_acts[0]: true,
		some_acts[3]: true,
		some_acts[7]: true,
		some_acts[10]: true,
	}
	if !reflect.DeepEqual(sol, sole) {
		t.Errorf("%v != %v", sol, sole)
	}
}

func TestHuffmanQueue(t *testing.T) {
	chars := []HNode{
		{Char: 'f', Freq: 5},
		{Char: 'b', Freq: 13},
		{Char: 'c', Freq: 12},
		{Char: 'a', Freq: 45},
		{Char: 'e', Freq: 9},
		{Char: 'd', Freq: 16},
	}
	echars := []HNode{
		{Char: 'f', Freq: 5},
		{Char: 'e', Freq: 9},
		{Char: 'c', Freq: 12},
		{Char: 'b', Freq: 13},
		{Char: 'd', Freq: 16},
		{Char: 'a', Freq: 45},
	}
	qalloc := HHeap(make([]HNode, 0))
	q := &qalloc
	for _, char := range chars {
		q.MinInsert(char)
	}
	for i := 0; i < 8; i++ {
		min, ok := q.ExtractMin();
		var echar HNode
		if i < len(echars) {
			echar = echars[i]
			if !ok {
				t.Errorf("wrong status flag")
			}
		} else {
			echar = HNode{}
			if ok {
				t.Errorf("wrong status flag")
			}
		}
		if !reflect.DeepEqual(min, echar) {
			t.Errorf("%v != %v", min, echar)
		}
	}
}

func htree_eq(ht1, ht2 *HNode) bool {
	if ht1 == nil || ht2 == nil {
		if ht1 == nil && ht2 == nil {
			return true
		} else {
			return false
		}
	}
	return ht1.Freq == ht2.Freq &&
		ht1.Char == ht2.Char &&
		htree_eq(ht1.Left, ht2.Left) &&
		htree_eq(ht1.Right, ht2.Right)
}

func TestHuffman(t *testing.T) {
	chars := []HNode{
		{Char: 'f', Freq: 5},
		{Char: 'e', Freq: 9},
		{Char: 'c', Freq: 12},
		{Char: 'b', Freq: 13},
		{Char: 'd', Freq: 16},
		{Char: 'a', Freq: 45},
	}
	eht := HNode{
		Freq: 100,
		Left: &HNode{Freq: 45, Char: 'a'},
		Right: &HNode{
			Freq: 55,
			Left: &HNode{
				Freq: 25,
				Left: &HNode{Freq: 12, Char: 'c'},
				Right: &HNode{Freq: 13, Char: 'b'},
			},
			Right: &HNode{
				Freq: 30,
				Left: &HNode{
					Freq: 14,
					Left: &HNode{Freq: 5, Char: 'f'},
					Right: &HNode{Freq: 9, Char: 'e'},
				},
				Right: &HNode{Freq: 16, Char: 'd'},
			},
		},
	}
	ht := Huffman(chars)
	if !htree_eq(&ht, &eht) {
		t.Errorf("unexpected tree")
	}
}

