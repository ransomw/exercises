"use strict";


var myParseInt = function (str) {
  return parseInt(str);
};

var sumDigits = function (intN) {
  var expStrs = intN.toString().split('e+');
  var nextDigit;
  if (expStrs.length === 1) {
    return expStrs[0].split('')
      .map(myParseInt)
      .reduce(function(a,b){return a+b;});
  }
  nextDigit = parseInt(expStrs[0].split('.')[0]);
  return nextDigit +
    sumDigits(intN % Math.pow(10, parseInt(expStrs[1])));
};

console.log(sumDigits(Math.pow(2, 1000)));
