"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var offSet = 1;
  var i;
  var nRows;
  var inputs = [];
  for (i = 0; i < T; i += 1) {
    nRows = parseInt(fileLines[offSet].split(' ')[0]);
    inputs.push(fileLines.slice(offSet + 1, offSet + 1 + nRows)
                .map(function (line) {
                  return line.split(' ').map(myParseInt);
                }));
    offSet += 1 + nRows;
  }
  return inputs;
};

var getMaxs = function (input) {
  var i, j;
  var rowMax = [];
  var colMax = [];
  for (i = 0; i < input.length; i += 1) {
    rowMax[i] = 0;
  }
  for (i = 0; i < input[0].length; i += 1) {
    colMax[i] = 0;
  }
  for (i = 0; i < input.length; i += 1) {
    for (j = 0; j < input[0].length; j += 1) {
      rowMax[i] = Math.max(rowMax[i], input[i][j]);
      colMax[j] = Math.max(colMax[j], input[i][j]);
    }
  }
  return {
    row: rowMax,
    col: colMax
  };
};

var getOutput = function (input) {
  var max = getMaxs(input);
  var i, j;
  for (i = 0; i < input.length; i += 1) {
    for (j = 0; j < input[0].length; j += 1) {
      if (input[i][j] < max.row[i] &&
          input[i][j] < max.col[j]) {
        return 'NO';
      }
    }
  }
  return 'YES';
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

var outputs = getInputs(fs.readFileSync('B-large-practice.in', 'utf8')
                        .split('\n'))
  .map(getOutput);
fs.writeFileSync('B-large-practice.out', getOutputStr(outputs));
