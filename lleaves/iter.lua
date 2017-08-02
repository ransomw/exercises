-- this is the "complete" demo of the generic for

-- function closure as "iterator"
function cl_iter ()
   local linked_list = {car=1, cdr={car=2, cdr={car=3, cdr=nil}}}
   return function ()
      if not linked_list then
         return nil
      end
      local rv = linked_list.car
      linked_list = linked_list.cdr
      return rv
   end
end

for x in cl_iter() do
   print(x)
end

print()

--- note that this style of iterators can have helpers
function cl_iter_idx ()
   local arr = {1, 2, 3}
   local idx = 1
   return function ()
      if idx > 3 then
         return nil
      end
      -- idx += 1 --
      idx = idx + 1
      return arr[idx]
   end
end

for x in cl_iter() do
   print(x)
end

print()

local iter

do
   local iter_h = function (arr, idx)
      return arr[idx], idx
   end

   iter = function (arr)
      local idx = 0

      return function ()
         next, idx = iter_h(arr, idx + 1)
         -- look ahead in case like {1, nil, 1}?
         if next == nil then
            return nil
         end
         return next
      end
   end
end

for x in iter({1, 2, 3}) do
   print(x)
end

----

print()

