"use strict";

var range = function (a, b) {
  if (b === undefined) {
    b = a;
    a = 0;
  }
  if (b < a) {
    throw new Error();
  }
  return Array.apply(null, Array(b-a))
    .map(function (_, i) { return i + a; });
};

var makeGetFactors = function () {
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
    var factors = [];
    var i = 0;
    var p;
    while (N > 1) {
      if(primes[i] === undefined) {
        addNextPrime();
      }
      p = [primes[i], 0];
      if (p[i] > N) {
        throw new Error();
      }
      while (N % p[0] === 0) {
        N /= p[0];
        p[1] += 1;
      }
      if (p[1] !== 0) {
        factors.push(p);
      }
      i += 1;
    }
    return factors;
  };
};

var getFactors = makeGetFactors();


var NUM = 4;

var numFactors = range(1, NUM+1).map(function (N) {
  return getFactors(N).length;
});

var i = NUM;

while (true) {
  console.log(i);
  if (numFactors
      .filter(function (i) {return i !== NUM;}).length === 0) {
    console.log('FOUND');
    console.log(i-NUM+1);
    break;
  }
  i += 1;
  numFactors.splice(0, 1);
  numFactors.push(getFactors(i).length);
}
