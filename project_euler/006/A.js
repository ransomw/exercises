"use strict";

var findSum = function (num) {
  var i, j;
  var sum = 0;
  for (i = 1; i <= num; i += 1) {
    for (j = i + 1; j <= num; j += 1) {
      sum += i*j;
    }
  }
  return sum;
};

console.log(2*findSum(100));
