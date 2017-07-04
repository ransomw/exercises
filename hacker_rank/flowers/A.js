var myParseInt = function (str) {
  return parseInt(str);
};

var cmpNum = function (a, b) {
  return a - b;
};

var input = "3 2\n2 5 6";

var inputLines = input.split('\n');
var K = parseInt(inputLines[0].split(' ')[1]);
var prices = inputLines[1].split(' ')
      .map(myParseInt).sort(cmpNum).reverse();
var totPrice = 0;
var currNum = 0;
while (prices.length > 0) {
  totPrice += prices.splice(0, K)
    .map(function (price) {
      return price * (currNum + 1);
    }).reduce(function (a, b) {return a+b;});
  currNum += 1;
};
console.log(totPrice);
