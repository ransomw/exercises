module Sand where

import Prelude

import Data.Array (null, (..), filter, concatMap)
import Data.Array.Partial (head, tail)
import Data.Foldable (foldl, foldr, product)
import Partial.Unsafe (unsafePartial)

length :: forall a. Array a -> Int
length arr =
  if null arr
  then 0
  else 1 + length ((unsafePartial tail) arr)
       -- note unsafePartial applied to function
       -- (unsafe tail arr) is equivalent

isEven :: Int -> Boolean
isEven n =
  if n < 0
  then isEven (-n)
  else if n == 0
       then true
       else if n == 1
            then false
            else isEven (n - 2)

numEvens :: Array Int -> Int
numEvens arr =
  if null arr
  then 0
  else let remEvens = numEvens (unsafePartial tail arr)
       in if isEven (unsafePartial head arr)
          then 1 + remEvens
          else remEvens

-- demo map + eta conversion + anon fn
addOneToAll :: Array Int -> Array Int
addOneToAll = map (\x -> x + 1)

-- demo infix operator
doubleAll :: Array Int -> Array Int
doubleAll arr = (\x -> x * 2) `map` arr

-- demo functor map (infix version of haskell's `fmap`)
-- point being (at this point) that, for Arrays, fmap is map
additiveInverseAll :: forall a. Ring a => Array a -> Array a
additiveInverseAll arr = (\x -> -x) <$> arr

-- or, to demo a functor on morphism between distinct objects
-- and use prefix notation to make clear that F(mor) is mor
-- .. F(mor) still does the same thing (array-ifies it)
--    to each object, however, which is still only an example of the
--    general definiton of mathematical functors that
--    may assoc any object w/ any other object, provided
--    (1) morphisms compose under the functor and
--    (2) identities (morphisms) are preserved
-- Q: are haskell-dialect functors therefore less general
--   in that they have kind * -> * and must use exactly one concrete
--   typeclass in order to specify how they act on all objects?
-- note how the original category (Show) is dragged along w/ the functor,
-- ...... still some mismatch w/ math ideas:
-- functors associate morphism to morphism _only_, not object to object
showAll :: forall a. Show a => Array a -> Array String
showAll = (<$>) show

----
-- demo infix declaration
addToAll :: Int -> Array Int -> Array Int
addToAll y = map (\x -> x + y)

-- number 0-9 is precedence, w/ larger precedence bracked earlier
infix 3 addToAll as @@

someRangeOne = 4 @@ (1 .. 5)

----
-- 4.7 exercises
sqAll :: forall a. Semiring a => Array a -> Array a
sqAll = map (\x -> x * x)

nonNeg :: forall a. (Ord a, Semiring a) => Array a -> Array a
nonNeg = filter (\x -> x >= zero)

infix 3 filter as <$?>

nonNegInt :: Array Int -> Array Int
nonNegInt intArr = (\x -> x >= 0) <$?> intArr

----
-- 4.8

flatSquaresArr :: Array Int
flatSquaresArr = concatMap (\x -> [x, x * x]) (1 .. 4)
-- [1,1,2,4,3,9,4,16]

----
-- 4.9

-- factors (i.e. pairs of integers) of a given integer
factors :: Int -> Array (Array Int)
factors n =
  -- note use of fold in `product` function
  filter (\p -> product p == n) (pairs n)
  where
    -- distinct pairs of non-neg integers leq given integer
    pairs :: Int -> Array (Array Int)
    pairs n = concatMap
              (\i -> map (\j -> [i, j]) (i .. n))
              (1 .. n)

----
-- 4.10 `do` notation

-- list monad (learn you a haskell example)
elemsAndNegsOne :: forall a. Ring a => Array a -> Array a
elemsAndNegsOne arr = arr >>= \x -> [x, -x]

elemsAndNegsTwo :: forall a. Ring a => Array a -> Array a
elemsAndNegsTwo arr =
  arr >>= (\x ->
            [x, -x])

elemsAndNegsThree :: forall a. Ring a => Array a -> Array a
elemsAndNegsThree arr = do
  x <- arr
  [x, -x]

-- todo: purescript by example examples

----
-- 4.11 guards

--- XXX todo XXX
-- this is a Control.MonadZero (guard), not a | guard

----
-- 4.12 folds

foldlEx :: String
foldlEx = foldl (\acc n -> acc <> show n) "" [1,2,3,4,5]
-- "12345"

foldrEx :: String
foldrEx = foldr (\n acc -> acc <> show n) "" [1,2,3,4,5]
-- "54321"

----
-- 4.13 tail recursion

-- js 没有

----
-- 4.14
-- 4.15

-- workarounds for lack of tail recursion

----
-- 4.16 a virtual filesystem

-- provides type definitions for Data.Path functions
-- root :: Path
-- ls :: Path -> Array Path
-- filename :: Path -> String
-- size :: Path -> Maybe Number
-- isDirectory :: Path -> Boolean

----
--
