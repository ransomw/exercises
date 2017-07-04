"use strict";

var mul = function(a, b) {
  return a*b;
};

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
    }
  };
};

var primeUtils = makePrimeUtils();
var getFactors = primeUtils.getFactors;
var getNPrimes = primeUtils.getNPrimes;

var N = 1;
while (getNPrimes(N).reduce(mul) < 1000000) {
  console.log(N);
  N += 1;
}

console.log(getNPrimes(N - 1).reduce(mul));

// [5, 6, 10, 11, 12, 3].forEach(function (N) {
//   console.log(N +' ==========');
//   var p;
//   var factors = getFactors(N);
//   for (p in factors) {
//     console.log(p+'^'+factors[p]);
//   }
// });


// var i;
// for (i = 2; i <= 1000000; i += 1) {
//   console.log(i);
//   getFactors(i);
// }
