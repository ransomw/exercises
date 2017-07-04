"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var getInput = function (line) {
  var seq = line.split(' ');
  return {
    S: parseInt(seq[1]),
    p: parseInt(seq[2]),
    scores: seq.slice(3).map(myParseInt)
  };
};

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var inputs = [];
  var i;
  for (i = 0; i < T; i += 1) {
    inputs.push(getInput(fileLines[1 + i]));
  }
  return inputs;
};

var getOutput = function (input) {
  var maxScores = input.scores.map(function (score) {
    return Math.ceil(score/3);
  });
  var i;
  var remS = input.S;
  var numBest = 0;
  for (i = 0; i < maxScores.length; i += 1) {
    if (maxScores[i] >= input.p) {
      numBest += 1;
    } else if (remS > 0 &&
               maxScores[i] === input.p - 1 &&
               input.scores[i] >= 2 &&
               input.scores[i] % 3 !== 1) {
      remS -= 1;
      numBest += 1;
    }
  }
  return numBest;
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

var outputs = getInputs(fs.readFileSync('B-small-practice.in', 'utf8')
                        .split('\n'))
  .map(getOutput);
fs.writeFileSync('B-small-practice.out', getOutputStr(outputs));
