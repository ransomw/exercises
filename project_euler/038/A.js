"use strict";

var _ = require('lodash');

var cmpNum = function (a, b) {
  return a - b;
};

var isPan = function (N) {
  var nStr = N.toString();
  return nStr.indexOf(0) === -1 &&
    nStr.length === _.unique(nStr).length &&
    _.unique(nStr).length === 9;
};

var getCProd = function (N) {
  var cProd = '';
  var i = 1;
  while (cProd.length < 9) {
    cProd += N * i;
    i += 1;
  }
  return parseInt(cProd);
};

var pcp = [];

var i;
var cProd;

for (i = 1; i < 50000; i += 1) {
  cProd = getCProd(i);
  if (isPan(cProd)) {
    pcp.push(cProd);
  }
}

pcp.sort(cmpNum);
console.log(pcp[pcp.length - 1]);
