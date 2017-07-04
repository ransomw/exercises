module Picture where

import Prelude

import Data.Foldable (foldl)
-- import .. as .. for qualified names, e.g., Math.max
import Global as Global
import Math as Math
import Data.Array.Partial (head, tail)
import Partial.Unsafe (unsafePartial)
import Data.Foldable (sum)
import Data.Maybe (Maybe(..))


uTail = unsafePartial tail

---- ?
-- > :t sum
-- forall a f.
--   ( Foldable f
--   , Semiring a
--   ) => f a -> a
--
-- ... so what's up with typeclasses?
-- like, they can be "stacked" arbitrarily?
-- i.e. there could another class `g` for a function `g f a -> a`?
-- A1: algebraic data type constructors may include other ADTs

----
-- 5.3 simple pattern matching

-- Euclid's algorithm
-- ... for non-negative only
gcdOne :: Int -> Int -> Int
gcdOne n 0 = n
gcdOne 0 m = m
gcdOne n m = if n > m
          then gcdOne (n - m) m
          else gcdOne n (m - n)

-- rule for pattern matching in function definitions:
-- each case is tried in order, and the first match is evaluated

----
-- 5.4

-- types of patterns:
--  - literals (String, Int, Boolean, Number, Char)
--  - wildcards

booleanFromString :: String -> Boolean
booleanFromString "true" = true
booleanFromString _ = false

-- the above illustrates wildcard patterns.
-- wildcard patterns do not bind the wildcard `_` arg

----
-- 5.5 guards

gcdTwo :: Int -> Int -> Int
gcdTwo n 0 = n
gcdTwo 0 m = m
gcdTwo n m
  | n > m = gcdTwo (n - m) m
  | otherwise = gcdTwo n (m - n)

-- execises

fact :: Int -> Int
fact 0 = 1
fact n = n * (fact (n - 1))

choose :: Int -> Int -> Int
choose n k
  | k == 0 = 1
  | k == n = 1
  | otherwise = (prev (k - 1)) + (prev k)
  where prev k
          | k < n = choose (n - 1) k
          | otherwise = 1


----
-- 5.6 array patterns

isEmpty :: forall a. Array a -> Boolean
isEmpty [] = true
isEmpty _ = false

takeFive :: Array Int -> Int
takeFive [0, 1, a, b, _] = a * b
takeFive _ = 0

-- may only match arrays of fixed len due to perf concerns
-- Data.List for other types of matching

----
-- 5.7 record patterns and row polymorphism

showPersonOne :: { first :: String, last :: String } -> String
showPersonOne { first: f, last: l } = l <> ", " <> f

-- this type is "row polymorphism": allows extra keys on records
showPersonLoose :: forall r.
                   {first :: String
                   , last :: String | r } -> String
showPersonLoose { first: f, last: l } = f <> " " <> l <> ", esq."

-- ... so,
-- showPersonLoose {first: "name", last: "name", other: 123}
-- is still valid

-- also, to demonstrate alternate syntax
showPersonTwo :: { first :: String, last :: String } -> String
showPersonTwo p = p.last <> ", " <> p.first

----
-- 5.8 nested patterns

onlyMe :: Array { first :: String, last :: String } -> Boolean
onlyMe [{first: "ransom"}] = true
onlyMe _ = false

-- nesting applies only to arrays and records (i think?)

----
-- 5.9 named patterns
sortPair :: Array Int -> Array Int
sortPair arr@[x, y] -- `@` notation brings variables x, y into scope
  | x <= y = arr
  | otherwise = [y, x]
sortPair arr = arr

----
-- exercises

-- todo: 1 & 2

-- 3
fromSingleton :: forall a. a -> Array a -> a
fromSingleton _ arr@[x] = x
fromSingleton defaultVal arr = defaultVal

----
-- 5.10 case expressions
-- think "anonymous function"

-- Least Zero Suffix:
-- return the longest suffix of the array that sums to zero

lzsOne :: Array Int -> Array Int
lzsOne [] = []
lzsOne xs = case sum xs of
  0 -> xs
  _ -> lzsOne (uTail xs)


lzsTwo :: Array Int -> Array Int
lzsTwo [] = []
lzsTwo xs
  | sum xs == 0 = xs
  | otherwise = lzsTwo (uTail xs)

----
-- 5.11 pattern match failures and partial functions

failsEveryCall = \true -> true
-- this only fails on `false`
unsafeExample = unsafePartial \true -> true

----
-- 5.12 algebraic data types

data Point = Point {
  x :: Number,
  y :: Number
  }

-- each of `Circle`, `Line`, etc. is a constructor _function_
-- note that constructors may have the same name as type type iteslf
data Shape =
  Circle Point Number |
  Rectangle Point Number Number |
  Line Point Point |
  Text Point String

----
-- 5.13 using ADTs

myLineOne :: Shape
myLineOne = Line p1 p2
  where
    p1 :: Point
    p1 = Point { x: 1.0, y: 2.0 }

    p2 :: Point
    p2 = Point { x: 4.0, y: 6.0 }


showPoint :: Point -> String
showPoint (Point {x: x, y: y}) =
  "(" <> (show x) <> ", " <> (show y) <> ")"

-- note that parens around Shape constructors may not be omitted
-- for pattern matching on showShape arg
showShape :: Shape -> String
showShape (Circle c r) =
  "Circle with center " <> (showPoint c) <>
  " and radius " <> (show r)
showShape (Rectangle c w h) = "Rectangle"
showShape (Line start end) = "Line"
showShape (Text loc text) =
  "Text '" <> text <> "' at point " <> (showPoint loc)

----
-- 5.14 Record puns
-- entirely sugar for readability

-- names (i.e. `x` and `y`) must match those of the properties
-- in the data type record definition
showPointPunned :: Point -> String
showPointPunned (Point {x, y}) =
  "(" <> (show x) <> ", " <> (show y) <> ")"

-- names must match here too
origin :: Point
origin = Point {x, y}
  where
    x = 0.0
    y = 0.0

----
-- exercises

--- 1
myCircleOne :: Shape
myCircleOne = Circle c 10.0
  where
    c :: Point
    c = Point { x: 0.0, y: 0.0 }

--- 2
-- scale shapes by an arbitrary factor
-- ???? "center the origin"
-- scaleShape :: Number -> Shape -> Shape
-- scaleShape scale (Circle c r) =
-- scaleShape scale (Rectangle c w h) =
-- scaleShape scale (Line start end) =
-- scaleShape scale (Text loc text) =

--- 3
textFromShape :: Shape -> Maybe String
textFromShape (Text loc text) = Just text
textFromShape _ = Nothing

----
-- 5.15 Newtypes

-- a special case of ADTs wherein
-- (1) there is exactly one constructor, and
-- (2) the constructor takes exactly one argument

newtype Pixels = Pixels Number
newtype Inches = Inches Number

-- .. so newtypes conceptually function as aliases *with type saftey*.
-- they will be used in conjunction with typeclasses in the next chap.

----
-- 5.16 A library for vector graphics

-- hearkening back to Calendar.purs in chap. 3,
-- when there was a list of calendar entries.
-- ... this was described as a "type synonym",
-- ?? so (presumably?) type safety checks treat
-- `Array Shape` and `Picture`
-- as the same
type Picture = Array Shape

-- now note the difference between type constructors and
-- type constructor functions:
-- Shape, Array, and List are type constructors,
-- and these type constructors have (possibly synonymous)
-- type constructor functions.
--
-- type constructor functions have types, and type constructors
-- have kinds ... the latter will presumably be discussed more later

-- recall eta conversion from chap. 4
showPicture :: Picture -> Array String
showPicture = map showShape

-- w/o eta conversion,
-- > :t (map showShape)
-- forall t1. (Functor t1) => t1 Shape -> t1 String

----
-- 5.17 computing bounding rectangles

data Bounds =
  Bounds
  {
    top :: Number
  , left :: Number
  , bottom :: Number
  , right :: Number
  }

emptyBounds :: Bounds
emptyBounds =
  Bounds
  {
    top: 0.0
  , left: 0.0
  , right: 0.0
  , bottom: 0.0
  }

-- smallest bounding rectangle for a shape

shapeBounds :: Shape -> Bounds
shapeBounds (Circle (Point {x, y}) r) =
  Bounds {
  top: y + r
  , left: x - r
  , right: x + r
  , bottom: y - r
  }
shapeBounds (Rectangle (Point {x, y}) w h) =
  Bounds {
  top: y + h
  , left: x
  , right: x + w
  , bottom: y
  }
shapeBounds (Line (Point {x: x1, y: y1}) (Point {x: x2, y: y2})) =
  Bounds {
  top: Math.max y1 y2
  , left: Math.min x1 x2
  , right: Math.max x1 x2
  , bottom: Math.min y1 y2
  }
-- shapeBounds (Text loc text) =
shapeBounds _ = Bounds {
  top: 0.0
  , left: 0.0
  , right: 0.0
  , bottom: 0.0
  }



-- smallest bounding rectangle for a picture
-- bounds :: Picture -> Bounds
-- bounds = foldl combine emptyBounds
--   where
--     combine :: Bounds -> Shape -> Bounds
--     combine bounds shape = (shapeBounds shape) \/ bounds

