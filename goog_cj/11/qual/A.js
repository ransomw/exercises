"use strict";

var fs = require('fs');

var getInput = function (line) {
  var seq = line.split(' ');
  var N = parseInt(seq[0]);
  var input = [];
  var i;
  for (i = 0; i < N; i += 1) {
    input.push({
      bot: seq[1 + 2*i],
      button: parseInt(seq[2 + 2*i])
    });
  }
  return input;
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

var otherBot = function (bot) {
  if (bot === 'O') {
    return 'B';
  }
  if (bot === 'B') {
    return 'O';
  }
  throw new Error("unexpected input to otherBot");
};

var getNextButton = function(input, bot, start) {
  var i;
  for (i = start; i < input.length; i += 1) {
    if (input[i].bot === bot) {
      return input[i].button;
    }
  }
  return null;
};

var getOutput = function (input) {
  var botPos = {'O': 1, 'B': 1};
  var i;
  var totTime = 0;
  var currTime;
  var prevBot;
  var otherBotNext;
  var otherBotDist;
  for (i = 0; i < input.length; i += 1) {
    currTime = Math.abs(botPos[input[i].bot] - input[i].button) + 1;
    botPos[input[i].bot] = input[i].button;
    totTime += currTime;
    if (prevBot !== input[i].bot) {
      otherBotNext = getNextButton(input, otherBot(input[i].bot), i);
    }
    prevBot = input[i].bot;
    if (otherBotNext !== null) {
      otherBotDist = Math.abs(botPos[otherBot(input[i].bot)]
                              - otherBotNext);
      if (otherBotDist <= currTime) {
        botPos[otherBot(input[i].bot)] = otherBotNext;
      } else {
        if (botPos[otherBot(input[i].bot)] <= otherBotNext) {
          botPos[otherBot(input[i].bot)] += currTime;
        } else {
          botPos[otherBot(input[i].bot)] -= currTime;
        }
      }
    }
  }
  return totTime;
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

var inputs = getInputs('A-large-practice.in');
var outputs = inputs.map(getOutput);
fs.writeFileSync('A-large-practice.out', getOutputStr(outputs));
