"use strict";

var makeIsPrime = function () {
  var primes = [2, 3];

  var isNextPrime = function(next) {
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

  var addNextPrime = function () {
    var next = primes[primes.length-1] + 2;
    while (true) {
      if (isNextPrime(next)) {
        primes.push(next);
        return;
      }
      next += 2;
    }
  };

  return function (N) {
    var nRt = Math.sqrt(N);
    while (primes[primes.length - 1] <= nRt) {
      addNextPrime();
    }
    return isNextPrime(N);
  };
};

var isPrime = makeIsPrime();

var cornerVals = function (N) {
  return [N*N, N*N - N + 1, N*N - 2*N + 2, N*N - 3*N + 3];
};
var i = 3;
var nPVal, nCVal;
var totPVal = 0, totCVal = 0, totVal = 0;
var ratio;
while (true) {
  nPVal = cornerVals(i).filter(isPrime).length;
  nCVal = 4 - nPVal;
  totPVal += nPVal;
  totCVal += nCVal;
  totVal += 4;
  if (totVal != totPVal + totCVal) {
    throw new Error();
  }
  ratio = totPVal / totVal;
  console.log(ratio +' '+i+' '+totPVal+' '+totVal);
  if (ratio < .1) {
    break;
  }
  i += 2;
};
