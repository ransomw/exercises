print("calling some C functions from lua...")

print("dist_sq(3, 4) -> " .. dist_sq(3, 4))

print("calling with a checked non-numeric argument " ..
         "dist_sq(\"asdf\", 4)")
print(dist_sq("asdf", 4)) -- => 16

--------
-- uncomment to see error message
-- "bad argument #2 to `dist_sq' (number expected, got string)"
-- ... doing so will crash the rest of this lua script, however
-- ====
-- print("calling with a checked non-numeric argument " ..
--          "dist_sq(3, \"asdf\")")
-- print(dist_sq(3, "asdf"))
--------

print("mylib.dist_sq(3, 4) -> " .. mylib.dist_sq(3, 4))
