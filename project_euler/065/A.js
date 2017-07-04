"use strict";

var gcd = function (a, b) {
  if (b === 0) {
    return a;
  }
  return gcd(b, a % b);
};

var simplify = function (frac) {
  var fGcd = gcd(frac[0], frac[1]);
  return [frac[0]/fGcd, frac[1]/fGcd];
};


console.log(simplify([41, 29]));
console.log(simplify([99, 70]));
console.log(simplify([239, 169]));
console.log(simplify([577, 408]));
console.log(simplify([1393, 985]));
console.log(simplify([3363, 2378]));
