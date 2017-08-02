-- looks like a js Object,
-- tho the lua community wants to call it an "associative array"
a = {}

-- ... quacks like a duck, too
a[1] = 'asdf'
a['qwer'] = 3
a.zxcv = 1
print(a[1])
print(a['qwer'])
print(a.qwer)
print(a) -- gives a (labelled) addr in memory

-- loopy already
b = {}
for idx=1,10 do -- iterator?
   b[idx] = 2 * idx
end
print(b[5])
print(b[11]) --nil

-- and destruct
for k, v in b do
   print(k .. ' ' .. v)
end
