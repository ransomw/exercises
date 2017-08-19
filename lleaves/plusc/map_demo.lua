print("lua testing map function defined in C")

my_arr = {3, 4, 5}
sq_the_thing = function (x) return x^2 end
map(my_arr, sq_the_thing)
print("4^2 == " .. my_arr[2] .. "?")
