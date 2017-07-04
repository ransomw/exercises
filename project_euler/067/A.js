"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var triangle = fs.readFileSync('triangle.txt', 'utf8').split('\n')
      .filter(function (line) {
        return line.trim() !== '';
      })
      .map(function (line) {
        return line.split(' ').map(myParseInt);
      }).reverse();

var maxPath = Array.apply(null, Array(triangle.length))
      .map(function () {return [];});
maxPath[0] = triangle[0];
var i, j;
for (i = 1; i < triangle.length; i += 1) {
  for (j = 0; j < triangle[i].length; j += 1) {
    maxPath[i][j] = triangle[i][j] +
      Math.max(maxPath[i-1][j], maxPath[i-1][j+1]);
  }
}

debugger;

console.log(maxPath[maxPath.length - 1][0]);
