var myParseInt = function (str) {
  return parseInt(str);
};

var cmpNum = function (a, b) {
  return a - b;
};

var input = "7 50\n1 12 5 111 200 1000 10";

var inputLines = input.split('\n');

var K = parseInt(inputLines[0].split(' ')[1]);
var prices = inputLines[1].split(' ').map(myParseInt)
      .sort(cmpNum).reverse();
var nextPrice = prices.pop();
var remAmt = K;
var numToys = 0;
while(remAmt >= nextPrice) {
  numToys += 1;
  remAmt -= nextPrice;
  nextPrice = prices.pop();
}

console.log(numToys);
