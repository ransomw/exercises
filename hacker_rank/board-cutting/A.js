var myParseInt = function (str) {
  return parseInt(str);
};

var getCases = function (input) {
  var inputLines = input.split('\n');
  var T = parseInt(inputLines.splice(0,1)[0]);
  var cases = [];
  while (inputLines.length > 0) {
    inputLines.splice(0,1);
    cases.push(inputLines.splice(0,2).map(
      function (line) {
        return line.split(' ').map(myParseInt);
      }));
  }
  return cases;
};

var LRG_MOD = Math.pow(10, 9) + 7;

var getOutput = function (X, Y) {
  var nCutX = 1;
  var nCutY = 1;
  var cost = 0;
  X.sort();
  Y.sort();
  while(X.length > 0 || Y.length > 0) {
    if (Y.length === 0 ||
        X[X.length - 1] > Y[Y.length - 1]) {
      cost += (nCutY * X.pop()) % LRG_MOD;
      nCutX += 1;
    } else {
      cost += (nCutX * Y.pop()) % LRG_MOD;
      nCutY += 1;
    }
  }
  return cost;
};

var input = "2\n2 2\n2\n1\n6 4\n2 1 3 1 4\n4 1 2";

getCases(input).forEach(function (XY) {
  console.log(getOutput(XY[0], XY[1]));
});
