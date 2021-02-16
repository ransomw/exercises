(ns dev
  (:require [clojure.zip :as zip]))

;; zippers intro
;; http://www.exampler.com/blog/2010/09/01/editing-trees-in-clojure-with-clojurezip/

;; this is a tree
(def orig [1 '(a b c) 2])

;; this is a tree in a zipper
(def rl (zip/seq-zip (seq orig)))

;; this is a location in the tree .. see below
(def b (-> rl zip/down zip/right zip/down zip/right))

(comment
  "navigating within a static tree"

  ;; this is navigating to nodes in the tree in the zipper
  (zip/node (zip/down rl)) ;; => 1
  (-> rl zip/down zip/right zip/node) ;; => (a b c)
  (-> rl zip/down zip/right zip/down zip/right zip/node) ;; => b
  (-> rl zip/down zip/rightmost zip/node) ;; => 2

  ;; more navigation functions
  [zip/left zip/up zip/leftmost]

  ;; this is navigating to multi-node parts of the tree
  (-> rl zip/down zip/right zip/lefts) ;; => (1)
  (-> rl zip/down zip/right zip/rights) ;; => (2)
  (-> rl zip/down zip/right zip/down zip/rights) ;; => (b c)
  (-> b zip/path) ;; => [(1 (a b c) 2) (a b c)]

  )

;; these are locations in a modified tree in a zipper
(def rm-abc (zip/remove (zip/up b)))
(def rm-b (zip/remove b))

(comment
  "modifying trees in zippers"

  ;; `root` gives the entire tree with modifications
  (zip/root rm-b) ;; => (1 (a c) 2)
  ;; `node` returns the tree with modifications
  (map zip/node [rm-abc rm-b]) ;; => (1 a)
  ;; `path` returns the tree without modifications
  (zip/path rm-b) ;; => [(1 (a b c) 2) (a b c)]
  ;; as with navigation, leftmost and/or rightmost may need special care
  (zip/node (-> b zip/left zip/remove)) ;; => (b c)
  ;; `edit` modifies a location like `swap` modifies an atom
  (-> rl (zip/edit conj 27) zip/root) ;; => (27 1 (a b c) 2)
  ;; there are more location-modifying functions
  [zip/insert-left zip/insert-right zip/replace
   zip/insert-child zip/append-child]

  )

(comment
  "a couple of functions to view zippers as iterators"

  ;; `next` is depth-first
  (-> rl zip/next zip/next zip/next zip/node) ;; => a
  ;; `end?` can be used to check how these walks are going
  (-> rl zip/end?) ;; => false
  (-> rm-abc zip/next zip/next zip/end?) ;; => true
  ;; it's possible to walk without `next`
  (-> rm-abc zip/right zip/end?) ;; => false
  (-> rm-abc zip/right zip/next zip/end?) ;; => true
  ;; it's not possible (?) to reach `end?` without `next`
  (try (-> rm-abc zip/right zip/right zip/end?)
       (catch Exception e
         (type e))) ;; => java.lang.NullPointerException
  (-> rm-abc zip/rightmost zip/end?) ;; => false

  )
