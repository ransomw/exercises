var myParseInt = function (str) {
  return parseInt(str);
};

var input = "10 4\n2 5 3 6";
// var input = "4 3\n1 2 3";

var inputLines = input.split('\n');
var N = parseInt(inputLines[0].split(' ')[0]);
var amts = inputLines[1].split(' ').map(myParseInt);

var numWays = [];

var getNumWays = function(N, lastIdx) {
  var lastC = amts[lastIdx];
  var remAmt = N;
  var numWays = 0;
  if (lastIdx === 0) {
    if (N % amts[0] === 0) {
      return 1;
    }
    return 0;
  }
  while (remAmt >= 0) {
    numWays += getNumWays(remAmt, lastIdx - 1);
    remAmt -= lastC;
  }
  return numWays;
};

console.log(getNumWays(N, amts));

// var getNumWays = function(N, C) {
//   var lastC = C.slice(-1)[0];
//   var otherC = C.slice(0, -1);
//   var remAmt = N;
//   var numWays = 0;
//   if (C.length === 1) {
//     if (N % C[0] === 0) {
//       return 1;
//     }
//     return 0;
//   }
//   while (remAmt >= 0) {
//     numWays += getNumWays(remAmt, otherC);
//     remAmt -= lastC;
//   }
//   return numWays;
// };

///////////////////////////////////////////////

// var numWays = [
//   Array.apply(null, Array(N + 1)).map(function (_, i) {
//     if (i % amts[0] === 0) {
//       return 1;
//     }
//     return 0;
//   })
// ];
// var i, j;
// for (i = 1; i < amts.length; i += 1) {
//   numWays[i] = [];
//   for(j = 0; j <= N; j += 1) {
//     if (j - amts[i] >= 0) {
//       numWays[i][j] = numWays[i - 1][j] + numWays[i - 1][j - amts[i]];
//     } else {
//       numWays[i][j] = numWays[i - 1][j];
//     }
//   }
// };
// numWays.forEach(function (row) {console.log(row.join(' '));});



