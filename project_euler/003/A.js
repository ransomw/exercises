"use strict";

var cmpNum = function (a, b) {
  return a - b;
};

var isPrime = function (num) {
  var i;
  var numSqrt = Math.sqrt(num);
  if (num === 1) {
    return false;
  }
  if (num === 2) {
    return true;
  }
  for (i = 2; i < numSqrt; i += 1) {
    if (num % i === 0) {
      return false;
    }
  }
  return true;
};

var largestPrimeFactor1 = function (num) {
  var factors = [];
  var i;
  var numSqrt = Math.sqrt(num);
  for (i = 2; i < numSqrt; i += 1) {
    if (num % i === 0) {
      factors.push(i);
      factors.push(num / i);
    }
  }
  console.log("found prime factors");
  factors.sort(cmpNum);
  factors.reverse();
  for (i = 0; i < factors.length; i += 1) {
    if (isPrime(factors[i])) {
      return factors[i];
    }
  }
  return undefined;
};

console.log(largestPrimeFactor1(600851475143));
