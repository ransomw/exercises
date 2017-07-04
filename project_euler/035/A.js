"use strict";

var _ = require('lodash');

var isNextPrime = function(primes, next) {
  var nextSqrt = Math.sqrt(next);
  var i;
  for (i = 0; i < primes.length; i += 1) {
    if (primes[i] > nextSqrt) {
      return true;
    }
    if (next % primes[i] === 0) {
      return false;
    }
  }
  return true;
};


var firstPrimes = function (max) {
  var primes = [2];
  var next = 3;
  while (primes[primes.length - 1] < max) {
    if (isNextPrime(primes, next)) {
      primes.push(next);
    }
    next += 1;
  }
  primes.pop();
  return primes;
};

var rotate = function (N, i) {
  var nStr = N.toString();
  return parseInt(nStr.slice(i) + nStr.slice(0, i));
};

var getRotations = function (N) {
  return Array.apply(null, Array(N.toString().length - 1))
    .map(function (_, i) {return rotate(N, i + 1);});
};

console.log(getRotations(123));

var PRIMES = firstPrimes(1000000);
// var PRIMES = firstPrimes(100);
var cPrimes = [];

console.log(PRIMES);

var isCPrime = function (P) {
  console.log("testing "+P);
  var rotations = getRotations(P);
  var i, j;
  for (i = 0; i < rotations.length; i += 1) {
    if (PRIMES[_.sortedIndex(PRIMES, rotations[i])] !== rotations[i]) {
      return false;
    }
  }
  return true;
};

console.log(
PRIMES.filter(isCPrime).length
);
