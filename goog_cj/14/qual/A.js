"use strict";

var fs = require('fs');

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var i;
  var inputs = [];
  for (i = 0; i < T; i += 1) {
    inputs.push({
      firstRowIdx: parseInt(fileLines[1 + 10*i]) - 1,
      secondRowIdx: parseInt(fileLines[6 + 10*i]) - 1,
      firstSquare: fileLines.slice(2 + 10*i, 6 + 10*i)
        .map(function (line) {return line.split(' ');}),
      secondSquare: fileLines.slice(7 + 10*i, 11 + 10*i)
        .map(function (line) {return line.split(' ');})
    });
  }
  return inputs;
};

var getOutput = function (input) {
  var firstRow = input.firstSquare[input.firstRowIdx];
  var secondRow = input.secondSquare[input.secondRowIdx];
  var match = undefined;
  var i;
  for (i = 0; i < firstRow.length; i += 1) {
    if (secondRow.indexOf(firstRow[i]) !== -1) {
      if (match === undefined) {
        match = firstRow[i];
      } else {
        return "Bad magician!";
      }
    }
  }
  if (match) {
    return match;
  }
  return "Volunteer cheated!";
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

var outputs = getInputs(fs.readFileSync('A-small-practice.in', 'utf8')
                        .split('\n'))
  .map(getOutput);
fs.writeFileSync('A-small-practice.out', getOutputStr(outputs));
