"use strict";

var p, a, b;
var maxP, currN, maxN = 0;
for (p = 2; p <= 1000; p += 2) {
  currN = 0;
  for (a = 1; a < p/2; a += 1) {
    b = (p*p - 2*p*a)/(2*p - 2*a);
    if (b === Math.floor(b)) {
      currN += 1;
    }
  }
  if (currN > maxN) {
    maxN = currN;
    maxP = p;
  }
}

console.log(maxP);
