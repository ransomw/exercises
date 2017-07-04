"use strict";

var gcd = function (a, b) {
  if (b === 0) {
    return a;
  }
  return gcd(b, a % b);
};

var lcm = function (a, b) {
  return (a / gcd(a, b)) * b;
};

console.log(
  Array.apply(null, Array(20)).map(function (_, i) {return i + 1;})
    .reduce(lcm)
);
