"use strict";

var fs = require('fs');

var getInputs = function () {
  var inFileContents = fs.readFileSync(process.argv[2], 'utf8');
  var inFileLines = inFileContents.split('\n');
  var numInputs = parseInt(inFileLines[0]);
  var inputs = [];
  var i;
  var currOffset = 1;
  var currNumEngines;
  var currNumSearches;

  for (i = 0; i < numInputs; i += 1) {
    currNumEngines = parseInt(inFileLines[currOffset]);
    if (isNaN(currNumEngines)) {
      throw new Error("currNumEngines NaN");
    }
    currNumSearches = parseInt(inFileLines[currOffset+currNumEngines+1]);
    if (isNaN(currNumSearches)) {
      throw new Error("currNumSearches NaN");
    }
    inputs[i] = {
      engines: inFileLines.slice(currOffset+1,
                                 currOffset+currNumEngines+1),
      searches: inFileLines.slice(
        currOffset+currNumEngines+2,
        currOffset+currNumEngines+currNumSearches+2)
      };
    currOffset += currNumEngines + currNumSearches + 2;
  }

  return inputs;
};

var getOutput = function (input) {
  var engines = input.engines;
  var searches = input.searches;
  var numSwitches = 0;
  var unusedEngines = [];
  var i;
  for (i = 0; i < searches.length; i += 1) {
    if (unusedEngines.indexOf(searches[i]) === -1) {
      if (unusedEngines.length < engines.length - 1) {
        unusedEngines.push(searches[i]);
      } else {
        numSwitches += 1;
        unusedEngines = [searches[i]];
      }
    }
  }
  return numSwitches;
};

var inputs = getInputs();
var outputs = inputs.map(getOutput);
var i;
var outputStr = '';
for (i = 0; i < outputs.length; i += 1) {
  outputStr += "Case #" + (i+1).toString() + ": ";
  outputStr += outputs[i].toString();
  outputStr += '\n';
}
fs.writeFileSync(process.argv[3], outputStr);
