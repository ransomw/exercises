--- "numeric" for
-------------

for i=1,10,4 do
   print(i)
end
-- is sorta like `for` in C,
-- except for a few things: the i++/++i distinction is absent, for one

-- implicit `local` in `for`
print(i) -- nil

print()

-- also, this is an "assumed step size" of 1
for i=1,2 do
   print(i)
end

print()

do
   local function f (x)
      print("top of function") -- prints once
      return x + 1
   end

   local x = 2

   -- unlike py, not an iterator for this form
   -- for i=1,f(i) do -- fails
   for i=1,f(x) do
      print(i)
   end  -- 1\n2\n3
end

print()

do
   local sth
   for i=1,3 do
      if i == 2 then
         sth = i
         break
      end
   end
   print(sth)
end


--- "generic" for
-------------

print('"generic" for')
print()

-- these are of limited value due to the format `for ___ in fcn_i_dunno`
do
   local things = {'asdf', 'qwer'}
   local pointa = {['x']=3, ['y']=4}
   local pointb = {x=3, y=4}
   -- this definitely turns a table into an iterator
   for idx, v in ipairs(things) do
      print(idx .. ' : ' .. v)
   end

   -- but what's the return type of `pairs`
   for x in pairs(pointb) do
      print(x)
   end -- x\ny
end
-- more on iterators anon

print()
-- idiomatic note
do
   days_of_the_week = {
      "Monday",
      "Tuesday",
      "Wednesday",
   }
   lookup_table = {} -- this is the thing, not .indexOf equivalent
   for idx, day in ipairs(days_of_the_week) do
      lookup_table[day] = idx
   end
   print(lookup_table["Tuesday"])
end


