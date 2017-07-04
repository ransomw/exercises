"use strict";

var MAX = Math.pow(10, 6);

var F = [undefined, 2];

var i, j;
for (i = 3; i <= MAX; i += 1) {
  console.log(i);
  F[i] = ((i+3)*i)/2;
  for (j = 2; j <= i; j += 1) {
    F[i] -= F[Math.floor(i/j)];
  }
}

console.log(F[MAX] - 2);
