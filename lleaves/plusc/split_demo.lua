print("lua testing split function defined in C")
my_str = "asdf qwer   zxcv"
split_res = split(my_str, ' ')

print('"' .. my_str .. '"')
print("splits on ' ' to")
for idx, val in ipairs(split_res)
do
   print('"' .. val .. '"')
end

