"use strict";

var maxW = function(k, A) {
  var W = [0];
  var i, j;
  for (i = 1; i <= k; i += 1) {
    W[i] = 0;
    for (j = 0; j < A.length; j += 1) {
      if (i - A[j] >= 0 &&
         A[j] + W[i-A[j]] > W[i]) {
        W[i] = A[j] + W[i-A[j]];
      }
    }
  }
  return W[k];
};

var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (input) {
  var inputLines = input.split('\n');
  var T = parseInt(inputLines[0]);
  var i;
  var inputs = [];
  for (i = 0; i < T; i += 1) {
    inputs.push({
      k: parseInt(inputLines[1 + 2*i].split(' ')[1]),
      A: inputLines[2 + 2*i].split(' ').map(myParseInt)
    });
  }
  return inputs;
};

var input = "2\n3 12\n1 6 9\n5 9\n3 4 4 4 8";

var inputs = getInputs(input);
var outputs = inputs.map(function (o) { return maxW(o.k, o.A);});
outputs.forEach(function (x) { console.log(x);});
