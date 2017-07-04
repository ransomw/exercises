


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

var f2n = function (frac) {
  return frac[0]/frac[1];
};

var r = [3, 7];
var x = Math.floor(1000000/r[1]);
console.log(x);
console.log(simplify([r[0]*x, r[1]*x]));
var l = simplify([r[0]*x-1, r[1]*x]);
console.log(l);
