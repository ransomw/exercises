"use strict";

var fs = require('fs');
var bn = require('bignum');


var myParseIntB = function (str) {
  return bn(str, 2);
};

var cmpNum = function (a, b) {
  if (a.gt(b)) {
    return 1;
  }
  if (b.gt(a)) {
    return -1;
  }
  return 0;
};

var getInput = function (input) {
  var inputLines = input.split('\n');
  var caseLines;
  var inputs = [];
  inputLines.splice(0, 1);
  while (inputLines.length >= 3) {
    caseLines = inputLines.splice(0, 3);
    inputs.push({
      outlets: caseLines[1].split(' ').map(myParseIntB),
      devices: caseLines[2].split(' ').map(myParseIntB)
    });
  }
  return inputs;
};

var arrEq = function(arr1, arr2) {
  var i;
  if (arr1.length !== arr2.length) {
    throw new Error();
  }
  for (i = 0; i < arr1.length; i += 1) {
    if (!arr1[i].eq(arr2[i])) {
      return false;
    }
  }
  return true;
};

var getOutput = function(input) {
  var firstOutlet = input.outlets[0];
  var remOutlets = input.outlets.slice(1);
  var devices = input.devices.slice();
  var i, j;
  var currDevice, remDevices, currSwitches, remOutletsSwitched;
  var numSwitches = function(dev) {
    return (firstOutlet.xor(dev)).toString(2).split('')
      .filter(function (d) {return d === '1';}).length;
  };
  devices.sort(function (da, db) {
    return numSwitches(da) - numSwitches(db);
  });
  for (i = 0; i < devices.length; i += 1) {
    remDevices = devices.slice();
    currDevice = remDevices.splice(i, 1)[0];
    currSwitches = firstOutlet.xor(currDevice);
    remOutletsSwitched = remOutlets.map(function (out) {
      return out.xor(currSwitches);
    });
    remDevices.sort(cmpNum);
    remOutletsSwitched.sort(cmpNum);
    if (arrEq(remDevices, remOutletsSwitched)) {
      return numSwitches(currDevice);
    }
  }
  return "NOT POSSIBLE";
};

var F_NAME='A-large-practice';

var inputs = getInput(fs.readFileSync(F_NAME+'.in', 'utf8'));
var outputs = inputs.map(getOutput);
fs.writeFileSync(
  F_NAME+'.out',
  outputs.map(function (res, i) {
    return 'Case #' + (i+1).toString() + ": " + res;
  }).join('\n')
);
