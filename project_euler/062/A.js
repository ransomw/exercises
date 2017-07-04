"use strict";

var bn = require('bignum');

var arePerms = function (N, M) {
  var nChars = N.toString().split('').sort();
  var mChars = M.toString().split('').sort();
  var i;
  if (nChars.length !== mChars.length) {
    return false;
  }
  for (i = 0; i < nChars.length; i += 1) {
    if (nChars[i] !== mChars[i]) {
      return false;
    }
  }
  return true;
};

var digitSum = function (N) {
  return N.toString().split('')
    .map(function (c) {return parseInt(c);})
    .reduce(function(a,b){return a+b;});
};

var partByPerms = function (arr) {
  var part = arr.map(function(elem){return [elem];});
  var i, j, currRep;
  for (i = 0; i < part.length; i += 1) {
    currRep = part[i][0];
    for (j = i + 1; j < part.length; j += 1) {
      while(part[j] && arePerms(currRep, part[j][0])) {
        part[i] = part[i].concat(
          part.splice(j, 1)[0]
        );
      }
    }
  }
  return part;
};

var cubes = Array.apply(null, Array(50000))
      .map(function (_, i) {
        return bn.pow(i, 3);
      });
var maxLen = cubes[cubes.length - 1].toString().length - 1;
console.log(maxLen);
var len, dSumHash, dSum, cubesOfLen;
var permsPart, minPartSize = 5;

for (len = 12; len <= maxLen; len += 1) {
  cubesOfLen = cubes.filter(function (N) {
    return N.toString().length === len;});
  dSumHash = [];
  cubesOfLen.forEach(function (N) {
    var dSum = digitSum(N);
    if (!dSumHash[dSum]) {
      dSumHash[dSum] = [N];
    } else {
      dSumHash[dSum].push(N);
    }
  });
  debugger;
  permsPart = [];
  for (dSum in dSumHash) {
    permsPart = permsPart.concat(
      partByPerms(dSumHash[dSum])
        .filter(function (set) {
          return set.length >= minPartSize;})
    );
  }
  console.log(len);
  console.log(permsPart);
}
