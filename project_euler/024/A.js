"use strict";

var fact = function (N) {
  return Array.apply(null, Array(N))
    .map(function (_, i) {return i + 1;})
    .reduce(function (a, b) {return a * b;});
};

var digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

// digits = [0, 1, 2];

var mPerm = '';

var remPerm = 1000000;
remPerm = 999999;

// remPerm = 4;

while (digits.length > 1) {
  var nextStartIdx = Math.floor(remPerm / fact(digits.length - 1));
  mPerm += digits.splice(nextStartIdx, 1)[0];
  remPerm -= nextStartIdx * fact(digits.length);
}

mPerm += digits.pop();

console.log(mPerm);
