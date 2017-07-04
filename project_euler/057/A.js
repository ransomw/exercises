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

var iter = function (frac) {
  var n = frac[0];
  var d = frac[1];
  var a = [d, n+d];
  return [a[0]+a[1], a[1]];
};

var frac = [1, 1];
var i;
var num = 0;
for (i = 0; i < 1000; i += 1) {
  frac = iter(frac);
  if (frac[0].toString().length > frac[1].toString().length) {
    num += 1;
  }
  console.log(i +': '+ frac+' : '+num);
}
console.log(num);
