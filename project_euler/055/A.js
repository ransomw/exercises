"use strict";

var bn = require('bignum');

var isPal = function (str) {
  var front = str.slice(0, Math.floor(str.length/2));
  var back = str.slice(Math.ceil(str.length/2));
  return front === back.split('').reverse().join('');
};

var lIter = function (N) {
  return N.add(N.toString().split('').reverse().join(''));
};

var isL = function (N) {
  var j;
  for (j = 0; j < 60; j += 1) {
    N = lIter(N);
    if (isPal(N.toString())) {
      return false;
    }
  }
  return true;
};


var i, j, N;
var numL = 0;
for (i = 5; i < 10000; i += 1) {
  N = bn(i);
  console.log(N.toString());
  if (isL(N)) {
    numL += 1;
  }
}

console.log(numL);
