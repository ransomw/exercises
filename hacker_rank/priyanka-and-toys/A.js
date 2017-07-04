var myParseInt = function (str) {
  return parseInt(str);
};

var cmpNum = function (a, b) {
  return a - b;
};

var input = "5\n1 2 3 17 10";

var weights = input.split('\n')[1].split(' ').map(myParseInt);
weights.sort(cmpNum).reverse();
var lastBought = weights.pop();
var nBought = 1;
var curr;
while (weights.length > 0) {
  curr = weights.pop();
  if (curr - lastBought > 4) {
    lastBought = curr;
    nBought += 1;
  }
}

console.log(nBought);
