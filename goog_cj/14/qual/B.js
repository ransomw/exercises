"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (fileLines) {
  var T = parseInt(fileLines[0]);
  var i;
  var inputs = [];
  var vals;
  for (i = 0; i < T; i += 1) {
    vals = fileLines[1 + i].split(' ').map(parseFloat);
    inputs.push({
      C: vals[0],
      F: vals[1],
      X: vals[2]
    });
  }
  return inputs;
};


var getNumSec = function (input, nFarms, secSoFar) {
  var secTilDone = input.X / (2 + input.F*nFarms);
  var secTilFarm = input.C / (2 + input.F*nFarms);
  var secTilDoneFarm = secTilFarm +
        (input.X / (2 + input.F*(nFarms + 1)));
  if (secTilDone < secTilDoneFarm) {
    return secSoFar + secTilDone;
  }
  return getNumSec(input, nFarms + 1, secSoFar + secTilFarm);
};

var getOutput = function (input) {
  return getNumSec(input, 0, 0).toFixed(7);
};

var getOutput1 = function (input) {
  var nFarms = 0;
  var secSoFar = 0;
  var secTilDone = input.X / (2 + input.F*nFarms);
  var secTilFarm = input.C / (2 + input.F*nFarms);
  var secTilDoneFarm = secTilFarm +
        (input.X / (2 + input.F*(nFarms + 1)));
  while (secTilDone > secTilDoneFarm) {
    secSoFar += secTilFarm;
    nFarms += 1;
    secTilDone = input.X / (2 + input.F*nFarms);
    secTilFarm = input.C / (2 + input.F*nFarms);
    secTilDoneFarm = secTilFarm +
      (input.X / (2 + input.F*(nFarms + 1)));
  }
  return (secSoFar + secTilDone).toFixed(7);
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
  .map(getOutput1);
fs.writeFileSync('B-large-practice.out', getOutputStr(outputs));
