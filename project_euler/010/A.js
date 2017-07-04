"use strict";


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


var firstPrimes = function (n) {
  var primes = [2];
  var next = 3;
  while (next < n) {
    if (isNextPrime(primes, next)) {
      primes.push(next);
    }
    next += 1;
  }
  return primes;
};

console.log(firstPrimes(2000000).reduce(function (a, b) {return a+b;}));
