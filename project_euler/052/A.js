"use strict";

var _ = require('lodash');

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

var TS = range(2, 7);

console.log(TS);

var x = 1;
while (true) {
  console.log(x);
  if (_.unique(
    TS.map(function (m) {
      return _.unique((m * x).toString()).sort().join('');
    })).length === 1) {
    break;
  }
  x += 1;
}
