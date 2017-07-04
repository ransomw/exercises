"use strict";

var _ = require('lodash');

var makePrimeUtils = function () {
  var primes = [2, 3];
  var memFactors = [];

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


  return {
    getFactors: function (N) {
      if (memFactors[N]) {
        return memFactors[N];
      }
      var newFactors = [], factors;
      var currPrime, divCount;
      var i = 0, nOrig = N, p;
      while (N > 1 && memFactors[N] === undefined) {
        while(primes[i] === undefined) {
          addNextPrime();
        }
        currPrime = primes[i];
        divCount = 0;
        if (currPrime > N) {
          throw new Error();
        }
        while (N % currPrime === 0 && memFactors[N] === undefined) {
          N /= currPrime;
          divCount += 1;
        }
        if (divCount !== 0) {
          newFactors[currPrime] = divCount;
        }
        i += 1;
      }
      if (N === 1) {
        factors = newFactors;
      } else {
        factors = memFactors[N].slice();
        for (p in newFactors) {
          if (factors[p] === undefined) {
            factors[p] = newFactors[p];
          } else {
            factors[p] += newFactors[p];
          }
        }
      }
      memFactors[nOrig] = factors;
      return factors;
    },
    getNPrimes: function (N) {
      while (primes.length < N) {
        addNextPrime();
      }
      return primes.slice(0, N);
    },
    getPrimesLt: function (max) {
      while (primes[primes.length - 1] < max) {
        addNextPrime();
      }
      return primes.filter(function (p) {return p < max;});
    },
    hasPFactLt: function (N, max) {
      while (primes[primes.length - 1] < max) {
        addNextPrime();
      }
      var rt = Math.sqrt(N);
      var i = 1;
      while (primes[i] < max && primes[i] <= rt) {
        if (N % primes[i] === 0) {
          return true;
        }
        i += 1;
      }
      return false;
    }
  };
};

var MAX = 1000000;

var primeUtils = makePrimeUtils();
var getPFacts = function (N) {
  var facts = primeUtils.getFactors(N);
  var pFacts = [];
  for (var p in facts) {
    pFacts.push(p);
  }
  return pFacts;
};

var primes = primeUtils.getPrimeLt();
