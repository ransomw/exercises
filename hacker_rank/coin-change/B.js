var myParseInt = function (str) {
  return parseInt(str);
};

var input = "10 4\n2 5 3 6";
// var input = "4 3\n1 2 3";

var inputLines = input.split('\n');
var N = parseInt(inputLines[0].split(' ')[0]);
var amts = inputLines[1].split(' ').map(myParseInt);

var numWays = [
  Array.apply(null, Array(N + 1)).map(function (_, i) {
    if (i % amts[0] === 0) {
      return 1;
    }
    return 0;
  })
];

var i, j;
var remAmt;
for (i = 1; i < amts.length; i += 1) {
  numWays[i] = [];
  for (j = 0; j <= N; j += 1) {
    remAmt = j;
    numWays[i][j] = 0;
    while (remAmt >= 0) {
      numWays[i][j] += numWays[i-1][remAmt];
      remAmt -= amts[i];
    }
  }
};

console.log(numWays[amts.length - 1][N]);

// numWays.forEach(function (row) {console.log(row.join(' '));});
