
do
   -- uncomment and see the below fail
   -- local function f1 ()
   function f1 ()
      local a, b = 1, 2
      -- although the following doesn't parse
      -- print(if a < b then a + b else a - b end)
      -- some one liners can be ok
      if a < b then return b else return a end
   end
   print(f1()) -- 2
end

print(f1()) -- 2

do
   local a, b = 1, 2
   if a ~= 1 then
      print(a)
   elseif b ~= 2 then
      print(b)
   else
      print("no python 'elif'.\n" ..
               -- neat (possibly ruby-like) convention: multiline as blocks
               "still, cleaner lexing " ..
               "than js, et. al. " ..
            "'else if'")
   end
end

