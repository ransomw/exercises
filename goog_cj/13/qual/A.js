"use strict";

var fs = require('fs');

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var inputs = [];
  var i;
  for (i = 0; i < T; i += 1) {
    inputs.push(fileLines.slice(1 + 5*i, 1 + 5*i + 4)
                .map(function (line) {return line.split('');}));
  }
  return inputs;
};

var getWinner = function (line) {
  var winner = undefined;
  var i;
  for (i = 0; i < line.length; i += 1) {
    if (line[i] === 'T') {
      continue;
    }
    if (line[i] === '.') {
      return undefined;
    }
    if (winner === undefined) {
      winner = line[i];
      continue;
    }
    if (line[i] !== winner) {
      return undefined;
    }
  }
  return winner;
};

var getLines = function (input) {
  var i, j;
  var lines = [];
  var line;
  // append rows
  for (i = 0; i < input.length; i += 1) {
    lines.push(input[i].slice(0));
  }
  // cols
  for (i = 0; i < input[0].length; i += 1) {
    line = [];
    for (j = 0; j < input.length; j += 1) {
      line.push(input[j][i]);
    }
    lines.push(line);
  }
  // diags
  line = [];
  for (i = 0; i < input.length; i += 1) {
    line.push(input[i][i]);
  }
  lines.push(line);
  line = [];
  for (i = 0; i < input.length; i += 1) {
    line.push(input[i][input.length - 1 - i]);
  }
  lines.push(line);
  return lines;
};

var getOutput = function (input) {
  var i, j;
  var lines = getLines(input);
  debugger;
  var winner = lines.map(getWinner)
        .filter(function (o) { return o !== undefined;})[0];
  if (winner) {
    return winner + " won";
  }
  for (i = 0; i < input.length; i += 1) {
    for (j = 0; j < input[0].length; j += 1) {
      if (input[i][j] === '.') {
        return "Game has not completed";
      }
    }
  }
  return "Draw";
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

var outputs = getInputs(fs.readFileSync('A-large-practice.in', 'utf8')
                        .split('\n'))
  .map(getOutput);
fs.writeFileSync('A-large-practice.out', getOutputStr(outputs));
