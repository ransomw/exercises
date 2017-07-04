"use strict";

var aCandidates = [];

var getA = function (b) {
  return {
    a: (500000 - 1000*b) / (1000 - b),
    b: b
  };
};

console.log(Array.apply(null, Array(498))
            .map(function (_, i) {return i + 2;})
            .map(getA)
            .filter(function (o) { return Math.floor(o.a) === o.a;})
           );
