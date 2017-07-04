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

var fracEq = function(frac1, frac2) {
  frac1 = simplify(frac1);
  frac2 = simplify(frac2);
  return frac1[0] === frac2[0] &&
    frac1[1] === frac2[1];
};

var n, d;
var cFracs = [];
var frac;
var nSimp;
for(d = 10; d < 100; d += 1) {
  for (n = 10; n < d; n += 1) {
    if(n.toString()[1] === d.toString()[0]) {
      nSimp = [parseInt(n.toString()[0]), parseInt(d.toString()[1])];
      if (fracEq(nSimp, [n, d])) {
        cFracs.push([n, d]);
      }
    }
  }
}

n = cFracs.map(function (frac) {return frac[0];})
  .reduce(function(a,b) {return a*b;});
d = cFracs.map(function (frac) {return frac[1];})
  .reduce(function(a,b) {return a*b;});

console.log(simplify([n, d]));
