---- what makes a coroutine a coroutine?
-- * its own call stack of function frames
-- * its own flow of execution (i.e.  pointer to main memory)
-- so there's the round robin async loop ..
-- .. and how and when to pause?
---------------------------------------------

-----------------------
-- local make_co = function ()
--    return coroutine.create(function ()
--       print("asdf")
--    end)
-- end
-- local co = make_co()
-----------------------

-- no sugared (e.g. `async def`) syntax (?)

local co = coroutine.create(function ()
      print("asdf")
end)

print(coroutine.status(co)) -- suspended
coroutine.resume(co) -- print from function
print(coroutine.status(co)) -- 'dead' x_X

print()

co = coroutine.create(function ()
      return "asdf"
end)
print(coroutine.resume(co)) -- true,  "asdf"
print(coroutine.resume(co)) -- false, "cannot resume dead coroutine"

print()

co = coroutine.create(function ()
      coroutine.yield("asdf")
end)
print(coroutine.resume(co)) -- true,  "asdf"
print(coroutine.resume(co)) -- true
print(coroutine.resume(co)) -- false, "cannot resume dead coroutine"

print()
print('----------')
print('----------')
print()

-- yield (from?)

co = coroutine.create(function ()
      for i=1,2 do
         print("co", i)
         coroutine.yield()
      end
      print("co", "exit")
end)

coroutine.resume(co) -- co 1 from in coro
print(coroutine.status(co)) -- suspended
coroutine.resume(co) -- co 2 from in coro
coroutine.resume(co) -- co exit from in coro
print(coroutine.status(co)) -- dead
coroutine.resume(co) -- no print

print()
print("---------")
print()

-- coro w/ params

co = coroutine.create(function (to_print)
      print(to_print)
end)

coroutine.resume(co, "stuff")

-- compare/contrast py `yield` (generator) with `yield from` (coro)
-- .. lua has coros, not generators.

print()
print("----------")
print()
-- table.getn -- array.length functional analogue for array-like tables
-- coroutine.wrap -- `functools.wraps` analogue, desugars to
function co_wrap (some_fn)
   local co = coroutine.create(some_fn)
   return function ()
      local status, res = coroutine.resume(co)
      return res
   end
end

-- ex.
-- generate all permutations of an "array" table
local sym

do
   -- in particular:  length of the table passed as
   --  separate param, unlike js
   -- local h_sym = function (arr, len)
   --    if len == 0 then

   -- sym =
end

-- ? libs for outer event loop implementations?
