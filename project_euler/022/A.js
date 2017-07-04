"use strict";

var fs = require('fs');

var input = fs.readFileSync('names.txt', 'utf8');

var letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

var names = input.split(',')
      .map(function (nameQ) { return nameQ.slice(1,-1); })
      .sort();

console.log(
names.map(function (name, i) {
  var nScore = name.split('').map(function (c) {
    return letters.indexOf(c) + 1;
  }).reduce(function (a,b) {return a+b;});
  return nScore * (i + 1);
}).reduce(function (a,b) {return a+b;})
);
