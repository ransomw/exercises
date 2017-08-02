days_of_the_week = {
   "Monday",
   "Tuesday",
   "Wednesday",
}
-- no trailing comma appears to be the standard
days_of_the_week_abbrev = {
   "Mon",
   "Tue",
   "Wed"
}

-- !watch out for the index
print(days_of_the_week[1])
print(days_of_the_week_abbrev[1]) --> Mon

-- =, not :
point = {
   x=3,
   y=4,
}
-- also note that it's _possible_ to parse this concatenation
print('('..point.x..', '..point.y..')')

-- not js, py
-- l = [1, 2, 3]
-- , although ..
linked_list = {car=1, cdr={car=2, cdr={car=3, cdr=nil}}}
while linked_list do
   print(linked_list.car)
   linked_list = linked_list.cdr
end
-- and there'll be an idiomatic array type later

-- "proper identifiers"
some_tokens = {
   -- '-'=1, -- parse error
   ['-']=1,
}
print(some_tokens['-'])
-- , so desugared
days_of_the_week_abbrev_desugared = {
   [1]="Mon",
   [2]="Tue"
}
point_desugared = {
   ['x']=3,
   ['y']=4,
}
print(days_of_the_week_abbrev_desugared[1]) --> Mon
print('('..point_desugared.x..', '..point_desugared.y..')')

-- and then this isn't totally sorted
comma_thing = {x=1, y=2; "one", "two", "三"}
print(comma_thing[3])
