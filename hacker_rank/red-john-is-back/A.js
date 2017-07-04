"use strict";

var getNumWays = function (maxLen) {
  var ways = [1, 1, 1, 1];
  var i;
  for (i = 4; i <= maxLen; i += 1) {
    ways[i] = ways[i - 1] + ways[i - 4];
  }
  return ways;
};

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
  while (next <= max) {
    if (isNextPrime(primes, next)) {
      primes.push(next);
    }
    next += 1;
  }
  return primes;
};

var MAX_LEN = 40;
var NUM_WAYS = getNumWays(MAX_LEN);
var FIRST_PRIMES = firstPrimes(NUM_WAYS[MAX_LEN]);
var NUM_PRIMES = NUM_WAYS.map(function (N) {
  return FIRST_PRIMES.filter(function (p) {
    return p <= N;
  }).length;
});

var myParseInt = function (str) {
  return parseInt(str);
};

var input = "2\n1\n7";

input.split('\n').slice(1).map(function (N) {
  return NUM_PRIMES[N];
}).forEach(function (x) {console.log(x);});


// console.log(NUM_WAYS);
// console.log(FIRST_PRIMES);
// console.log(NUM_PRIMES[7]);
