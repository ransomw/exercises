"use strict";

var amts = [1, 2, 5, 10, 20, 50, 100, 200];
var N = 200;

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
