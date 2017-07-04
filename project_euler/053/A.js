"use strict";

var bn = require('bignum');
var _ = require('lodash');

var NCR = [[bn(1)]];
var nextRow, prevRow;
var i;
while (NCR.length < 101) {
  prevRow = NCR[NCR.length - 1];
  nextRow = [bn(1)];
  for (i = 0; i < prevRow.length - 1; i += 1) {
    debugger;
    nextRow.push(prevRow[i].add(prevRow[i+1]));
  }
  nextRow.push(bn(1));
  NCR.push(nextRow);
}

console.log(
  _.flatten(NCR).filter(function (num) {
    return num.gt(1000000);  }).length
);
