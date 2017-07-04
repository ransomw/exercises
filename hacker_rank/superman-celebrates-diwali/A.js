"use strict";

var fs = require('fs');

var getMaxSaved = function(buildings, I) {
  var maxSaved = buildings.map(function (building) {
    return [building[0]];
  });
  var h, i;
  var maxAfterJump;
  for (h = 1; h < buildings[0].length; h += 1) {
    if (h - I >= 0) {
      maxAfterJump = Math.max.apply(
        null,
        maxSaved.map(function (building) {
          return building[h - I];
        }));
    } else {
      maxAfterJump = 0;
    }
    for (i = 0; i < buildings.length; i += 1) {
      maxSaved[i][h] = Math.max(maxSaved[i][h-1], maxAfterJump) +
        buildings[i][h]
        ;
    }
  }
  return Math.max.apply(
    null,
    maxSaved.map(function (building) {
      return building[building.length - 1];
    }));
};

var parseInput = function (input) {
  var inputLines = input.split('\n');
  var N = parseInt(inputLines[0].split(' ')[0]);
  var H = parseInt(inputLines[0].split(' ')[1]);
  var I = parseInt(inputLines[0].split(' ')[2]);
  var buildings = Array.apply(null, Array(N))
        .map(function () {
          return Array.apply(null, Array(H))
            .map(function () { return 0; });
        });
  var i;
  for (i = 1; i < inputLines.length; i += 1) {
    inputLines[i].split(' ').slice(1).forEach(
      function (nStr) {
        buildings[i - 1][parseInt(nStr) - 1] += 1;
      });
  }
  return {
    buildings: buildings,
    I: I
  };
};

// var input = "4 15 2 \n5 1 1 1 4 10\n8 9 5 7 7 3 9 8 8\n5 9 5 6 4 3\n0";

var input = fs.readFileSync('10.in', 'utf8');

var parsedInput = parseInput(input);
console.log(getMaxSaved(parsedInput.buildings, parsedInput.I));
