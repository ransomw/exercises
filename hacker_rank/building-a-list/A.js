"use strict";

var makeList = function (str) {
  var mask;
  var maskL;
  var list = [];
  for (mask = 1; mask < Math.pow(2,str.length); mask += 1) {
    maskL = mask.toString(2).split('').reverse()
      .map(function (x, i) {
        if (x === '1') {
          return i;
        }
        return undefined;
      }).filter(function (i) {
        return i !== undefined;
      });
    list.push(
      maskL.map(function (i) {
        return str[i];
      }).join('')
    );
  }
  list.sort();
  return list;
};

var input = "2\n2\nab\n3\nxyz";

var inputLines = input.split('\n');
var T = parseInt(inputLines[0]);
var inputs = Array.apply(null, Array(T))
      .map(function (_, i) {
        return inputLines[2+2*i];
      });
var outputs = inputs.map(makeList);
outputs.forEach(function (output) {
  output.forEach(function (str) {
    console.log(str);
  });
});

//   .forEach(function (str) {
//   console.log(str);
// });
