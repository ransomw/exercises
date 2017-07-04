"use strict";

var _ = require('lodash');

var LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// M: alphabet, N: string length

var not = function (fn) {
  return function() {
    return !fn.apply(null, arguments);
  };
};

// var not = function (fn) {
//   return function(x) {
//     return fn(x);
//   };
// };

var singleArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var containsPal = function (str) {
  var i;
  for (i = 0; i < str.length - 1; i += 1) {
    if (str[i] === str[i+1] ||
        str[i] === str[i+2]) {
      return true;
    }
  }
  if (str[i] === str[i+1]) {
    return true;
  }
  return false;
};

var getAPalWords = function (N, M) {
  var alphabet = LETTERS.slice(0, M);
  var words = alphabet.split('');
  var i, newWords;
  for (i = 1; i < N; i += 1) {
    newWords = [];
    alphabet.split('').forEach(function (c) {
      newWords = newWords.concat(
        words.map(function (w) {
          return w + c;
        })
      );
    });
    words = newWords;
  }
  if (_.unique(words).length !== words.length) {
    throw new Error();
  }
  // words.forEach(singleArg(console.log));
  return words.filter(not(containsPal));
};

var MOD = Math.pow(10, 9) + 7;

var calcNum = function (N, M) {
  var i;
  var num = M;
  if (N > 1) {
    num *= M - 1;
    num %= MOD;
  }
  for (i = 0; i < N - 2; i += 1) {
    num *= M - 2;
    num %= MOD;
  }
  return num;
};

var N = 6;
var M = 6;
var aPalWords = getAPalWords(N, M);
aPalWords.forEach(singleArg(console.log));
console.log(aPalWords.length + ' : ' + calcNum(N, M) );
