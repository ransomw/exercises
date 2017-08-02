-- the `local` _statement_

-- visible inside the function
local mult_const = 3

function make_obj ()
   -- this'll be visible outside the function, unlike py-
   b = {}
   -- -thon, where a `global` declaration might appear here
   local mult_const = mult_const -- idiomatic, apparently
   for idx=1,3 do
      -- contrary to Crockford, pil suggests _not_ declaring here
      local val -- however, duplicate declarations don't clashcrashbash
      if idx ~= 1 then
         mult_const = 2
      end
      local val = mult_const * idx
      b[idx] = val
   end
end

make_obj()

print(b[1]..','..b[2]..','..b[3]) -- 3,4,6
print(val) -- nil
print(mult_const) -- 3

-- ... and since "modules" are via tables ..
-- "global" namespace could get crowded?  --- i.e. still
-- don't understand what's local & global

-- anyways, here's a block all by itself
do
   local x = 1
   print(x) -- 1
end
print(x) -- nil
