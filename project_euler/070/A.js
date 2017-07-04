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

var MAX = Math.pow(10, 7);

var primeUtils = makePrimeUtils();
var getFactors = function (N) {
  var factors = [];
  var factArr = primeUtils.getFactors(N);
  for (var p in factArr) {
    factors.push([parseInt(p), factArr[p]]);
  }
  return factors;
};
var getNPrimes = primeUtils.getNPrimes;
var getPrimesLt = primeUtils.getPrimesLt;

var phi = function (N) {
  var factors = getFactors(N);
  var prod = N;
  factors.forEach(function (fact) {
    prod = prod - prod/fact[0];
  });
  return prod;
};

var isPerm = function (N, M) {
  return N.toString().split('').sort().join('') ===
    M.toString().split('').sort().join('');
};

var getFactStr = function (factors) {
  return factors.map(function (p) {return p[0]+'^'+p[1];})
    .join(' * ');
};

var method1 = function () {
  var i, currPhi, minRatio = 10, ratio, minRatioI, factors;
  var minDivP = 2;
  for (i = 3; i < 1000000; i += 2) {
    // if (primeUtils.hasPFactLt(i, minDivP)) {
    //   continue;
    // }
    if ((i - 1) % 100000 === 0) {
      console.log(i);
    }
    factors = getFactors(i);
    if (factors[0][0] < minDivP) {
      continue;
    }
    currPhi = phi(i);
    if (isPerm(i, currPhi)) {
      ratio = i/currPhi;
      console.log(
        i + ' = ' +
          getFactStr(factors) + ': ' +
          ratio
      );
      if (ratio < minRatio) {
        minRatio = ratio;
        minRatioI = i;
        minDivP = factors[0][0];
      }
    }
  }

  console.log(minRatioI+': '+minRatio);
};

var primes = getPrimesLt(100000);

var minDivP = 827;
var pIdx = primes.indexOf(minDivP);
var can, i, currPhi, ratio, minRatio = 2, minRatioN;
while(Math.pow(primes[pIdx], 2) < 10000000) {

  for (i = pIdx + 1; i < primes.length; i += 1) {
    can = primes[pIdx] * primes[i];
    if (can > 10000000) {
      break;
    }
    currPhi = phi(can);
    if (isPerm(can, currPhi)) {
      ratio = can/currPhi;
      console.log(can+' = '+primes[pIdx]+'*'+primes[i]+': '+ratio);
      if (ratio < minRatio) {
        minRatio = ratio;
        minRatioN = can;
      }
    }
  }
  pIdx += 1;
}

console.log(minRatioN+': '+minRatio);

// // var FIRST_PRIMES = getPrimesLt(MAX);
// var fact = getFactors(87109);
// for (var p in fact) {
//   console.log(p+'^'+fact[p]);
// }
