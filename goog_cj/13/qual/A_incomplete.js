"use strict";

var fs = require('fs');

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var inputs = [];
  var i;
  for (i = 0; i < T; i += 1) {
    inputs.push(fileLines.slice(1 + 4*i, 1 + 4*i + 4));
  }
  return inputs;
};

var getOutput = function (input) {
  var i, j;
  
};
