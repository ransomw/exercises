-- we've see `while` already:

while false do
   print("this won't print")
end

-- this is a joke about a vape flavor called "fruity loops",
-- which tastes like fruit loops...
local msg = "it tastes just like natural cerial!"
repeat
   print(msg)
   if string.find(msg, "natural") then
      msg = string.gsub(msg, "natural", '')
      msg = string.gsub(msg, ' '..' ', ' ')
   end
until not string.find(msg, "natural")
-- but then, i'm no george carlin..
print(msg)
-- ..although i am developing his hairline
