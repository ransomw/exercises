"use strict";

var numDiv_slow = function (N) {
  return Array.apply(null, Array(N))
    .map(function (_, i) {return i + 1;})
    .filter(function (d) {return N % d === 0;})
    .length;
};

var numDiv = function (N) {
  return Array.apply(null, Array(Math.floor(Math.sqrt(N))))
    .map(function (_, i) {return i + 1;})
    .filter(function (d) {return N % d === 0;})
    .length * 2;
};

var getNum = function () {
  var tNum;
  var nDiv;
  var i;
  for (i = 1; i < 100000; i += 1) {
    // tNum = Array.apply(null, Array(i))
    //   .map(function (_, i) {return i + 1;})
    //   .reduce(function (a, b) {return a+b;});
    tNum = (i*(i+1))/2;
    nDiv = numDiv(tNum);
    if (nDiv > 500) {
      return tNum;
    }
  }
  return null;
};


console.log(getNum());
