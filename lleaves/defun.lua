function lookup_a (some_table)
   return some_table.a
end

function plus_one (x)
   return x + 1
end

-- optional parens ...
x = lookup_a({a=1, b=2})
-- x = lookup_a{a=1, b=2)
print(x)
print(plus_one(1))
-- x = plus_one 1
-- print(x)
-- .. might not be so optional?

-- OOP
function not_this (this)
   return math.sqrt(math.exp(this.x, 2) + math.exp(this.y, 2))
end

point = {x=3, y=4, norm=not_this}
five = point:norm()
print(five)

-- just like js, no-arity
function and_things(a, b) return a and b end
print(and_things(1, 2)) -- 2
print(and_things(1)) -- nil
print(and_things(1,2,3,4,5)) -- 2

print()

idx_start, idx_end = string.find("asdfqwerasdf", "qwer")
print(idx_start ..' '.. idx_end) -- 5 8
-- or from the insides (perhaps not really a tuple, but..)
function return_nonsense_tuple ()
   return "asdf", "qwer"
end
asdf, qwer = return_nonsense_tuple()
print(qwer) -- qwer

-- and there aren't "too many/few values to unpack" as in py
-- ... forgoing some fiddling, but the gist is things
--     get assigned nil or discarded,
-- explaining things like
print(string.find("asdf", "sd"))
-- print(2, 3) -- same.
-- here, the end index gets discarded when the .. operator expr is evaluated
print("begin: " .. string.find("asdf", "sd"))

-- and for something totally different: {defun()}
for idx, thing in ipairs({return_nonsense_tuple()}) do
   print(idx ..': '.. thing)
end
-- side note to those concerned:
-- `defun` is the token for function declaration in e-lisp

-- probably some more neat language features here:
-- what's behind the {'asdf'; ?

print((string.find("asdf", "sd"))) -- 2

print(unpack({1, 2})) -- 1\s2
print(pairs({1, 2})) -- table

-- varargs
function sum (...)
   local tot = 0
   for idx, thing in ipairs(arg) do
      tot = tot + thing
   end
   return tot
end
print(sum(1, 2, 3, 4))
-- or
function sum_2 (r, ...)
   local tot = r
   for idx, thing in ipairs(arg) do
      tot = tot + thing
   end
   return tot
end
print(sum_2(1, 2, 3, 4))

print("use tables rather than kwargs")

-- anon
do
   table_to_sort = {2,1,3}
   table.sort(table_to_sort, function (a, b) return a > b end)
   for idx, val in ipairs(table_to_sort) do
      print(val)
   end
end

print((function (x) return x + 1 end)(1))

local no_hoist = function ()
   return "asdf"
end

print(no_hoist())

-- MUDs as an example of the the oft-touted and complex-sounding
-- "finite state machine" made possible via closures and clearing
-- the stack frame
