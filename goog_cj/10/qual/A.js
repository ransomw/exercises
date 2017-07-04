"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (filename) {
  var fileContents = fs.readFileSync(filename, 'utf8');
  var fileLines = fileContents.split('\n');
  var N = parseInt(fileLines[0]);
  var caseLines = fileLines.slice(1, N + 1);
  return caseLines.map(function (caseLine) {
    return caseLine.split(' ').map(myParseInt);
  });
};

var solveInput = function (input) {
  var N = input[0];
  var K = input[1];
  var i;
  var state = K.toString(2).split('').reverse();
  for (i = 0; i < N; i += 1) {
    if (state[i] === '0' || state[i] === undefined) {
      return 'OFF';
    }
  }
  return 'ON';
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


var inputs = getInputs('A-large-practice.in');
var outputs = inputs.map(solveInput);
var outputStr = getOutputStr(outputs);
fs.writeFileSync('A-large-practice.out', outputStr);

