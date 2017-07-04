"use strict";

var myParseInt = function (str) {
  return parseInt(str);
};

var getPowDigit = function (N, p) {
  return N.toString().split('')
    .map(myParseInt)
    .map(function (d) {return Math.pow(d, p);})
    .reduce(function (a,b) { return a+b; });
};

var pd = [];
var i;
var POW = 5;
var tp = Math.pow(10, POW + 1);
for (i = 2; i < tp; i += 1) {
  console.log(i+": "+pd);
  if (i === getPowDigit(i, POW)) {
    pd.push(i);
  }
};

console.log(pd.reduce(function (a,b) { return a+b; }));
