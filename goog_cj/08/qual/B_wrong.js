"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var timeStr2Mins = function (timeStr) {
  var hrsMins = timeStr.split(':').map(myParseInt);
  return (hrsMins[0] * 60) + hrsMins[1];
};

var timeStrs2Trip = function (timeStrs) {
  var depArrive = timeStrs.split(' ').map(timeStr2Mins);
  return {
    depart: depArrive[0],
    arrive: depArrive[1]
  };
};

var getInputs = function () {
  var inFileContents = fs.readFileSync('B-large-practice.in', 'utf8');
  var inFileLines = inFileContents.split('\n');
  var numInputs = parseInt(inFileLines[0]);
  var inputs = [];
  var i;
  var currOffset = 1;
  var currNs;

  for (i = 0; i < numInputs; i += 1) {
    currNs = inFileLines[currOffset + 1].split(' ').map(myParseInt);
    inFileLines.slice(currOffset + 2,
                      currOffset + 2 + currNs[0]);
    inFileLines.slice(currOffset + 2 + currNs[0],
                      currOffset + 2 + currNs[0] + currNs[1]);
    inputs[i] = {
      turn: parseInt(inFileLines[currOffset]),
      A2B: inFileLines.slice(currOffset + 2,
                             currOffset + 2 + currNs[0])
        .map(timeStrs2Trip),
      B2A: inFileLines.slice(currOffset + 2 + currNs[0],
                             currOffset + 2 + currNs[0] + currNs[1])
        .map(timeStrs2Trip)
    };
    currOffset += 2 + currNs[0] + currNs[1];
  }

  return inputs;
};

var getNumTrains = function (readyTrains, departures) {
  var numTrains = 0;
  var i;
  departures.sort();
  readyTrains.sort().reverse();
  for (i = 0; i < departures.length; i += 1) {
    if (readyTrains.length > 0 &&
        readyTrains[readyTrains.length - 1] <= departures[i]) {
      readyTrains.pop();
    } else {
      numTrains += 1;
    }
  }
  return numTrains;
};

var getOutput_broken = function (input) {
  var arrivalsA = input.B2A.map(function (o) {return o.arrive;});
  var departuresA = input.A2B.map(function (o) {return o.depart;});
  var arrivalsB = input.A2B.map(function (o) {return o.arrive;});
  var departuresB = input.B2A.map(function (o) {return o.depart;});
  var readiesA = arrivalsA.map(function (t) {return t + input.turn;});
  var readiesB = arrivalsB.map(function(t) {return t + input.turn;});
  return {
    numA: getNumTrains(readiesA, departuresA),
    numB: getNumTrains(readiesB, departuresB)
  };
};

var getOutput = function (input) {
  var T = input.turn;
  var trips = [];
  var trip;
  var i;
  var d;

  var start = [0, 0];
  var trains = [[], []];

  for (i = 0; i < input.A2B.length; i += 1) {
    trips.push([input.A2B[i].depart, input.A2B[i].arrive, 0]);
  }
  for (i = 0; i < input.B2A.length; i += 1) {
    trips.push([input.B2A[i].depart, input.B2A[i].arrive, 1]);
  }
  trips.sort(function (a, b) {
    if (a[0] < b[0]) {
      return -1;
    }
    if (a[0] > b[0]) {
      return 1;
    }
    return 0;
  });

  for (i = 0; i < trips.length; i += 1) {
    trip = trips[i];
    d = trip[2];
    if (trains[d].length > 0 &&
        trains[d][trains[d].length - 1] <= trip[0]) {
      trains[d].pop();
    } else {
      start[d] += 1;
    }
    trains[1 - d].push(trip[1] + T);
    trains[1 - d].sort().reverse();
  }
  return {
    numA: start[0],
    numB: start[1]
  };
};

var inputs = getInputs();
var outputs = inputs.map(getOutput);
debugger;
var i;
var outputStr = '';
for (i = 0; i < outputs.length; i += 1) {
  outputStr += "Case #" + (i+1).toString() + ": ";
  outputStr += outputs[i].numA.toString() + ' ';
  outputStr += outputs[i].numB.toString();
  outputStr += '\n';
}
fs.writeFileSync('B-large-practice.out', outputStr);
