"use strict";

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

var next = primes[primes.length - 1] + 2;

var isSum = function(primes, N) {
  var i, rt;
  for (i = 0; i < primes.length; i += 1) {
    rt = Math.sqrt((N - primes[i])/2);
    if (rt === Math.floor(rt)) {
      return true;
    }
  }
  return false;
};

while (true) {
  console.log(next);
  if (isNextPrime(primes, next)) {
    primes.push(next);
    next += 2;
    continue;
  }
  if (!isSum(primes, next)) {
    console.log('FOUND '+next);
    break;
  }
  next += 2;
}
