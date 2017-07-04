"use strict";

var _ = require('lodash');

var uniqDigits = function (N) {
  return N.toString().length === _.unique(N.toString()).length;
};

var a, b, p;
var na, nb, bMax;
var allDigits;
var pdRes = [];
for (a = 2; a < 100000; a += 1) {
  console.log("top of outer loop");
  if (uniqDigits(a)) {
    for (b = 1 ; b < 100000; b += 1) {
      if (uniqDigits(b)) {
        p = a * b;
        console.log('a: '+a+', b: '+b+', p: '+p);
        allDigits = p.toString() + a.toString() + b.toString();
        if (allDigits.length > 9) {
          console.log("breaking");
          break;
        }
        if (allDigits.length === 9 &&
            uniqDigits(allDigits) &&
            allDigits.indexOf('0') === -1) {
          pdRes.push({
            p: p,
            a: a,
            b: b
          });
        }
      }
    }
  }
}

debugger;

console.log(
  _.unique(pdRes.map(function(o){return o.p;})).reduce(function (a,b) {return a+b;})
);
