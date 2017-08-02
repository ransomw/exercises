a = "some thing"

print(a)

rv = string.gsub(a, "some", "another")

print(rv)
-- string.gsub doesn't mutate
print(a)

b = "thing two"
print(string.gsub(b, "two", "three"))
--> prints 'thing three<tab>1' <-- wtf?

print('and this') -- js/py quote conventions

-- backslash ascii
print('\97x')

-- multline
some_tex = [[

field [[\\mathbb{C}]]
]] --<-- lua-mode bug?

print(some_tex)

print("con" .. ' ' .. "cat")

-- print("co " + 1 + " erce") --err
print("12" + 24)
print("co " .. 1 .. " erce")
print(10 .. 24)
