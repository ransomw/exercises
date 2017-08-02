local Set = {}

Set.mt = {} -- metatable

Set.new = function (items)
   local set = {}
   setmetatable(set, Set.mt)
   for _, item in ipairs(items) do set[item] = true end
   return set
end

Set.toString = function (set)
   -- non-perf
   local str = ""
   -- pairs _not_ ipairs
   for item, _ in pairs(set) do
      str = str .. item .. ','
   end
   return str
end

-- very "blah" example of metamethods ..
-- others include
-- __mult, __eq, __lt, __le ... is this a complete list

Set.mt.__add = function (s1, s2)
   return Set.toString(s1) .. Set.toString(s2)
end

local some_set = Set.new({1, 2, 3})
local some_other_set = Set.new({3, 4, 5})
print(Set.toString(some_set))
print(Set.toString(some_other_set))
print(some_set + some_other_set)
