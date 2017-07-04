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
    next += 1;
  }
  return primes;
};

var isPerm = function (N, M) {
  var ns = N.toString();
  var ms = M.toString();
  return ns.split('').sort().join('') ===
    ms.split('').sort().join('');
};

var getSeq = function (arr) {
  var i, k, j;
  var a, b, c;
  var d, d1;
  if (arr.length < 3) {
    return null;
  }
  for (i = 0; i < arr.length - 2; i += 1) {
    a = arr[i];
    for (j = i + 1; j < arr.length - 1; j += 1) {
      b = arr[j];
      d = b - a;
      for (k = j + 1; k < arr.length; k += 1) {
        c = arr[k];
        d1 = c- b;
        if (d1 === d) {
          return [a, b, c];
        }
      }
    }
  }
  return null;
};

var PRIMES = firstPrimes(10000)
      .filter(function (N) {return N > 999;});

var allPerms = [];
var i;
var perms;
for (i = 0; i < PRIMES.length; i += 1) {
  console.log(PRIMES[i]);
  perms = PRIMES.filter(function (p) {
    return isPerm(PRIMES[i], p);
  });
  if (perms.length > 1) {
    allPerms.push(perms);
  }
}


allPerms.map(function (perm) {
  return getSeq(perm);
}).filter(function (o) {return o !== null;})
  .forEach(function (seq) {
    console.log(seq);
    console.log(seq.join(''));
  });

