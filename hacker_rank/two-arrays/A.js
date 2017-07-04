var myParseInt = function (str) {
  return parseInt(str);
};

var cmpNum = function (a, b) {
  return a - b;
};

var solveCase = function(C) {
  var a1 = C.arr1.sort(cmpNum);
  var a2 = C.arr2.sort(cmpNum).reverse();
  var i;
  for (i = 0; i < a1.length; i += 1) {
    if (a1[i] + a2[i] < C.K) {
      return 'NO';
    }
  }
  return 'YES';
};

var input = "2\n3 10\n2 1 3\n7 8 9\n4 5\n1 2 2 1\n3 3 3 4";

var inputLines = input.split('\n');
var T = parseInt(inputLines.splice(0, 1)[0]);
var caseLines;
var cases = [];
while (inputLines.length > 0) {
  caseLines = inputLines.splice(0, 3);
  cases.push({
    K: parseInt(caseLines[0].split(' ')[1]),
    arr1: caseLines[1].split(' ').map(myParseInt),
    arr2: caseLines[2].split(' ').map(myParseInt)
  });
}
cases.map(solveCase).forEach(function (res) {
  console.log(res);
});
