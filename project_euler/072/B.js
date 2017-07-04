"use strict";


var gcd = function (a, b) {
  if (b === 0) {
    return a;
  }
  return gcd(b, a % b);
};

var tot = 0;

var MAX = 1000000;
// MAX = 8;

var i, j;

for (i = 2; i <= MAX; i += 1) {
  tot += i - 1;
}

for (i = 2; i <= MAX; i += 1) {
  console.log(i);
  for (j = i + 1; j < MAX; j += 1) {
    tot -= gcd(i, j) - 1;
  }
}

console.log(tot);
