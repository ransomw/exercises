---------- possible change between versions:
--- error-handling with pcall ...
local err_func = function ()
   error("this function always creates an error")
end

local err_func_table = function ()
   error({msg="more detailed err message stucture"})
end

-- recall discards
res_a, res_b, res_c = pcall(err_func)
print(res_a) -- false
print(res_b) -- <filname>:<line_no>: <msg>
print(type(res_b)) -- string

res_a, res_b, res_c = pcall(print)
print(res_a) -- true
print(res_b) -- nil


print()

res_a, res_b, res_c = pcall(err_func_table)
print(res_a) -- false
print(res_b.msg) -- as above



-------------- prev version? note the block inversion
--- do skim for anon fn idiom

print("---------")
print()
print("---------")

--- protected call
-- note the block inversion
if pcall(err_func) then
   print("caught error")
else
   print("************ function didn't throw an error ...\n" ..
            "which, perplexingly, indicates an error")
end -- really, really lacking on comedic efforts -_-


print("---------")

-- pcall is just a function itself
pcall(err_func)

-- or, since pcall(fn) calls fn(...) with arg = {}
function non_neg (x)
   if x < 0 then
      error() -- err strings? exception classes? nada? -- or, how to construct?
   end
   return x
end

if pcall(function () non_neg(1) end) then
   print("****** misunderstanding error handling")
else
   print("yep, 1 >= 0")
end

if not pcall(function () non_neg(-1) end) then
   print("****** misunderstanding error handling")
end
