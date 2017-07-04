"use strict";

var cmpNum = function (a, b) {
  return a - b;
};

var isPal = function (num) {
  var str = num.toString();
  var pLen = Math.floor(str.length / 2);
  return str.slice(0, pLen) ===
    str.slice(-pLen).split('').reverse().join('');
};

var getMultiples = function () {
  var i, j;
  var multiples = [];
  for (i = 100; i < 999; i += 1) {
    for (j = i; j < 999; j += 1) {
      multiples.push(i * j);
    }
  }
  return multiples;
};

debugger;

console.log(getMultiples().filter(isPal).sort(cmpNum));
