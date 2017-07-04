"use strict";

var _ = require('lodash');
var bignum = require('bignum');

var a, b;
var arr = [];
var MAX = 5;
for (a = 2; a <= MAX; a += 1) {
  for (b = 2; b <= MAX; b += 1) {
    arr.push(Math.pow(a, b));
  }
}
console.log(_.unique(arr).length);
