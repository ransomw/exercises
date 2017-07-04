"use strict";

var fs = require('fs');

var getInput = function (line) {
  var lineS = line.split(' ');
  var nCom = parseInt(lineS[0]);
  var nOpp = parseInt(lineS[1 + nCom]);
  return {
    com: lineS.slice(1, 1 + nCom),
    opp: lineS.slice(2 + nCom, 2 + nCom + nOpp),
    seq: lineS[lineS.length - 1]
  };
};

var getInputs = function (filename) {
  var fileContents = fs.readFileSync(filename, 'utf8');
  var fileLines = fileContents.split('\n');
  var T = parseInt(fileLines[0]);
  var inputs = [];
  var i;
  for (i = 0; i < T; i += 1) {
    inputs.push(getInput(fileLines[1 + i]));
  }
  return inputs;
};

var findCom = function(coms, e1, e2) {
  var i;
  for (i = 0; i < coms.length; i += 1) {
    if ((coms[i][0] === e1 && coms[i][1] === e2) ||
        (coms[i][1] === e1 && coms[i][0] === e2)) {
      return coms[i][2];
    }
  }
  return null;
};

var containsOpp = function(opps, seq, el) {
  var i;
  for (i = 0; i < seq.length; i += 1) {
    if (findCom(opps, seq[i], el) === undefined) {
      return true;
    }
  }
  return false;
};

var getOutput = function (input) {
  var i;
  var output = [];
  var comTo;
  for (i = 0; i < input.seq.length; i += 1) {
    if (output.length === 0) {
      output.push(input.seq[i]);
      continue;
    }
    comTo = findCom(input.com, output.slice(-1)[0], input.seq[i]);
    if (comTo !== null) {
      output.pop();
      output.push(comTo);
      continue;
    }
    if (containsOpp(input.opp, output, input.seq[i])) {
      output = [];
      continue;
    }
    output.push(input.seq[i]);
  }
  return output;
};

var getOutputStr = function (outputs) {
  var i;
  var outputStr = '';
  for (i = 0; i < outputs.length; i += 1) {
    outputStr += "Case #" + (i+1).toString() + ": ";
    outputStr += '['+outputs[i].toString().replace(/,/g, ', ')+']';
    outputStr += '\n';
  }
  return outputStr;
};


var inputs = getInputs('B-large-practice.in');
var outputs = inputs.map(getOutput);
fs.writeFileSync('B-large-practice.out', getOutputStr(outputs));
