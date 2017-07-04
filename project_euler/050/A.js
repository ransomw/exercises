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


var firstPrimes = function (max) {
  var primes = [2];
  var next = 3;
  while (primes[primes.length-1] < max) {
    if (isNextPrime(primes, next)) {
      primes.push(next);
    }
    next += 2;
  }
  return primes;
};

var MIL = 1000000;

var PRIMES = firstPrimes(MIL);

var i, j;
var maxLen = 1, maxP = 2;
var currSum;
for (i = 0; i < PRIMES.length; i += 1) {
  currSum = PRIMES[i];
  if (currSum * 2 > MIL) {
    break;
  }
  for (j = i + 1; j < PRIMES.length; j += 1) {
    currSum += PRIMES[j];
    if (currSum > MIL) {
      break;
    }
    if (isNextPrime(PRIMES, currSum) &&
        j - i + 1 > maxLen) {
      maxLen = j - i + 1;
      maxP = currSum;
      console.log(maxP);
    }
  }
}
