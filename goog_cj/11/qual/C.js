"use strict";

var fs = require('fs');

var sortNum = function (a, b) {
  return a - b;
};

var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (filename) {
  var fileContents = fs.readFileSync(filename, 'utf8');
  var fileLines = fileContents.split('\n');
  var T = parseInt(fileLines[0]);
  var inputs = [];
  var i;
  for (i = 0; i < T; i += 1) {
    inputs.push(fileLines[2 + 2*i].split(' ').map(myParseInt));
  }
  return inputs;
};

var getOutput = function (input) {
  var xorAll = input[0];
  var i;
  var seanSum = 0;
  for (i = 1; i < input.length; i += 1) {
    xorAll ^= input[i];
  }
  if (xorAll !== 0) {
    return 'NO';
  }
  input.sort(sortNum);
  return input.slice(1).reduce(function (x, y) {return x + y;});
};


var getOutputStr = function (outputs) {
  var i;
  var outputStr = '';
  for (i = 0; i < outputs.length; i += 1) {
    outputStr += "Case #" + (i+1).toString() + ": ";
    outputStr += outputs[i];
    outputStr += '\n';
  }
  return outputStr;
};

var inputs = getInputs('C-large-practice.in');
var outputs = inputs.map(getOutput);
fs.writeFileSync('C-large-practice.out', getOutputStr(outputs));
