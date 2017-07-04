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

var PRIMES = [2, 3];

var addNextPrime = function(primes) {
  var next = primes[primes.length - 1] + 2;
  while (!isNextPrime(primes, next)) {
    next += 2;
  }
  primes.push(next);
  return primes;
};

var isPan = function (N) {
  var nStr = N.toString();
  return _.unique(nStr).sort().join('') ===
    Array.apply(null, Array(nStr.length))
    .map(function (_, i) {return (i + 1);}).join('');
};

var panP = [];

while (PRIMES[PRIMES.length - 1] < Math.pow(10, 9)) {
  console.log(PRIMES[PRIMES.length - 1] + ' ' + panP[panP.length-1]);
  if (isPan(PRIMES[PRIMES.length - 1])) {
    panP.push(PRIMES[PRIMES.length - 1]);
  }
  PRIMES = addNextPrime(PRIMES);
}

