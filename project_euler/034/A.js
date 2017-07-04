"use strict";

var myParseInt = function (str) {
  return parseInt(str);
};

var fact = function (N) {
  if (N === 0) {
    return 1;
  }
  return Array.apply(null, Array(N))
    .map(function (_, i) {return i + 1;})
    .reduce(function (a, b) {return a * b;});
};

var D_FACTS = Array.apply(null, Array(10))
      .map(function (_, i) {return fact(i);});

var sumFactDs = function (N) {
  return N.toString().split('').map(myParseInt)
    .map(function (d) {return D_FACTS[d];})
    .reduce(function (a, b) {return a+b;});
};

var i;
var cNums = [];
for (i = 10; i < 2600000; i += 1) {
  console.log("i: "+i+" "+cNums);
  if (i === sumFactDs(i)) {
    cNums.push(i);
  }
}

console.log(
  cNums.reduce(function (a, b) {return a+b;})
);
