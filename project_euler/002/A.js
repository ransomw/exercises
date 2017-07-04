"use strict";

var findSum = function () {
  var fibs = [1, 2];
  var i;
  var sum = 0;
  while (fibs[fibs.length - 2] + fibs[fibs.length - 1] <= 4000000) {
    fibs.push(fibs[fibs.length - 2] + fibs[fibs.length - 1]);
  }
  for (i = 0; i < fibs.length; i += 1) {
    if (fibs[i] % 2 === 0) {
      sum += fibs[i];
    }
  }
  return sum;
};


console.log(findSum());
