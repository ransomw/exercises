local Set = function (items)
   local set = {}
   for _, item in ipairs(items)
   do
      set[item] = true
   end
   return set
end

Set({1, 2, 3})

-- ? upstream libs?  std lib?
