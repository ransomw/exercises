var myParseInt = function (str) {
  return parseInt(str);
};

var getOutput = function (P) {
  var i;
  var maxSell = P.pop();
  var currP;
  var totalProfit = 0;
  while (P.length > 0) {
    currP = P.pop();
    if (currP < maxSell) {
      totalProfit += maxSell - currP;
    }
    maxSell = Math.max(maxSell, currP);
  }
  return totalProfit;
};

var getCases = function (input) {
  var inputLines = input.split('\n');
  var cases = [];
  inputLines.splice(0, 1);
  while (inputLines.length > 0) {
    inputLines.splice(0, 1);
    cases.push(inputLines.splice(0, 1)[0].split(' ').map(myParseInt));
  }
  return cases;
};

var input = "3\n3\n5 3 2\n3\n1 2 100\n4\n1 3 1 2";

getCases(input).forEach(function (P) {
  console.log(getOutput(P));
});
