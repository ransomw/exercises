"use strict";

var fs = require('fs');

var isPal = function (num) {
  var str = num.toString();
  var sArr = str.split('');
  var pLen = Math.floor(sArr/2);
  return sArr.slice(0, pLen).join('') ===
    sArr.slice(sArr.length - pLen, sArr.length).reverse().join('');
};

var findFairSquare = function (max) {
  var rtMax = Math.floor(Math.sqrt(max));
  var fairSquare = [];
  var i;
  var sq;
  for (i = 0; i < rtMax; i += 1) {
    if (isPal(i)) {
      sq = i * i;
      if (isPal(sq)) {
        fairSquare.push(sq);
      }
    }
  }
  return fairSquare;
};

var fairSquares = findFairSquare(Math.pow(10, 10));
