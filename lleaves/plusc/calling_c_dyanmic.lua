-- assert() checks for errors in loading
local mylib_loader = assert(loadlib("./calling_c.so", "add_my_lib"))
mylib_loader()
print("mylib.dist_sq(3, 4) -> " .. mylib.dist_sq(3, 4))
