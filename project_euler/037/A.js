"use strict";

var _ = require('lodash');

var primes = [2, 3, 5, 7];

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

var addNextPrime = function(primes) {
  var next = primes[primes.length - 1] + 2;
  while (!isNextPrime(primes, next)) {
    next += 2;
  }
  primes.push(next);
  return primes;
};

var isInSortedList = function (list, N) {
  return list[_.sortedIndex(list, N)] === N;
};

var lastIsTrunP = function (primes) {
  var pStr = primes[primes.length - 1].toString();
  var i;
  var tf, tb;
  for (i = 1; i < pStr.length; i += 1) {
    tf = parseInt(pStr.slice(0, i));
    tb = parseInt(pStr.slice(-i));
    if (!isInSortedList(primes, tf)) {
      return false;
    }
    if (!isInSortedList(primes, tb)) {
      return false;
    }
  }
  return true;
};

var trunPs = [];

while (trunPs.length < 11) {
  primes = addNextPrime(primes);
  if (lastIsTrunP(primes)) {
    trunPs.push(primes[primes.length - 1]);
    console.log(trunPs);
  }
}

console.log(trunPs.reduce(function(a,b) {return a+b;}));
