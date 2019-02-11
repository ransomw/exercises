package bintree

import "testing"
import (
	"reflect"
)

func link_parents(t *Tree) *Tree {
	if (t.Left != nil) {
		t.Left.P = t
		link_parents(t.Left)
	}
	if (t.Right != nil) {
		t.Right.P = t
		link_parents(t.Right)
	}
	return t
}

func tree_a() *Tree {
	return link_parents(&Tree{
	Left: &Tree{
		Left: &Tree{
			Key: 2,
		},
		Key: 5,
		Right: &Tree{
			Key: 5,
		},
	},
	Key: 6,
	Right: &Tree{
		Key: 7,
		Right: &Tree{
			Key: 8,
		},
	},
})
}

func tree_b1() *Tree {
	return link_parents(&Tree{
	Left: &Tree{
		Left: &Tree{
			Key: 5,
		},
		Key: 6,
	},
	Key: 7,
	Right: &Tree{
		Key: 8,
	},
})
}

func tree_b() *Tree {
	return link_parents(&Tree{
	Key: 2,
	Right: &Tree{
		Key: 5,
		Right: tree_b1(),
	},
})
}

func tree_c13() *Tree {
	return link_parents(&Tree{
	Key: 13,
	Left: &Tree{
		Key: 9,
	},
})
}

func tree_c1() *Tree {
	return link_parents(&Tree{
	Key: 6,
	Left: &Tree{
		Key: 3,
		Left: &Tree{
			Key: 2,
		},
		Right: &Tree{
			Key: 4,
		},
	},
	Right: &Tree{
		Key: 7,
		Right: tree_c13(),
	},
})
}

func tree_c() *Tree {
	return link_parents(&Tree{
	Key: 15,
	Left: tree_c1(),
	Right: &Tree{
		Key: 18,
		Left: &Tree{
			Key: 17,
		},
		Right: &Tree{
			Key: 20,
		},
	},
})
}

func TestInOrderWalk(t *testing.T) {
	sk := []int{2, 5, 5, 6, 7, 8}
	sk_a := tree_a().InOrderWalk()
	sk_b := tree_b().InOrderWalk()
	if !reflect.DeepEqual(sk, sk_a) {
		t.Errorf("%v != %v", sk, sk_a)
	}
	if !reflect.DeepEqual(sk, sk_b) {
		t.Errorf("%v != %v", sk, sk_b)
	}
}

func TestInOrderWalkStack(t *testing.T) {
	sk := []int{2, 5, 5, 6, 7, 8}
	sk_a := tree_a().InOrderWalkStack()
	sk_b := tree_b().InOrderWalkStack()
	if !reflect.DeepEqual(sk, sk_a) {
		t.Errorf("%v != %v", sk, sk_a)
	}
	if !reflect.DeepEqual(sk, sk_b) {
		t.Errorf("%v != %v", sk, sk_b)
	}
}

func TestInOrderWalkSuccessor(t *testing.T) {
	sk := []int{2, 5, 5, 6, 7, 8}
	sk_a := tree_a().InOrderWalkSuccessor()
	sk_b := tree_b().InOrderWalkSuccessor()
	if !reflect.DeepEqual(sk, sk_a) {
		t.Errorf("%v != %v", sk, sk_a)
	}
	if !reflect.DeepEqual(sk, sk_b) {
		t.Errorf("%v != %v", sk, sk_b)
	}
}

func TestMin(t *testing.T) {
	if tree_a().Min().Key != 2 {
		t.Errorf("tree a min")
	}
	if tree_b().Min().Key != 2 {
		t.Errorf("tree b min")
	}
	if tree_c().Min().Key != 2 {
		t.Errorf("tree c min")
	}
}

func TestMax(t *testing.T) {
	if tree_a().Max().Key != 8 {
		t.Errorf("tree a ")
	}
	if tree_b().Max().Key != 8 {
		t.Errorf("tree b ")
	}
	if tree_c().Max().Key != 20 {
		t.Errorf("tree c ")
	}
}

func TestMinR(t *testing.T) {
	if tree_a().MinR().Key != 2 {
		t.Errorf("tree a")
	}
	if tree_b().MinR().Key != 2 {
		t.Errorf("tree b")
	}
	if tree_c().MinR().Key != 2 {
		t.Errorf("tree c")
	}
}

func TestMaxR(t *testing.T) {
	if tree_a().MaxR().Key != 8 {
		t.Errorf("tree a ")
	}
	if tree_b().MaxR().Key != 8 {
		t.Errorf("tree b ")
	}
	if tree_c().MaxR().Key != 20 {
		t.Errorf("tree c ")
	}
}

func TestChkSearchPath(t *testing.T) {
	paths := [][]int{
	{2, 252, 401, 398, 330, 344, 397, 363},
	{924, 220, 911, 244, 898, 258, 362, 363},
	{925, 202, 911, 240, 912, 245, 363},
	{2, 399, 387, 219, 266, 382, 381, 278, 363},
	{935, 278, 347, 621, 299, 392, 358, 363},
	}
	for _, path := range paths {
		if r := ChkSearchPath(path); r != nil {
			t.Logf("%v %v", path, *r)
			return
		}
	}
	t.Errorf("no wrong path found")
}

