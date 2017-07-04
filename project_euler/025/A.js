"use strict";

var bigint = require('bigint');

var prevA = bigint(1);
var prevB = bigint(1);
var N = 3;
var next = prevA.add(prevB);
var tmp;
while(next.toString().length < 1000) {
  prevA = prevB;
  prevB = next;
  next = prevA.add(prevB);
  N += 1;
}

console.log('N: ' + N);
console.log(next.toString());
