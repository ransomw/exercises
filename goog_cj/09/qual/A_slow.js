"use strict";

var fs = require('fs');

var myParseInt = function (str) {
  return parseInt(str);
};

var parsePattern = function (line) {
  var i;
  var c;
  var inEntry = false;
  var entry = [];
  var pattern = [];
  for (i = 0; i < line.length; i++) {
    c = line[i];
    if (inEntry) {
      if (c === ')') {
        pattern.push(entry);
        entry = [];
        inEntry = false;
      } else {
        entry.push(c);
      }
    } else {
      if (c === '(') {
        inEntry = true;
      } else {
        pattern.push([c]);
      }
    }
  }
  return pattern;
};

var getInput = function (filename) {

  var fileContents = fs.readFileSync(filename, 'utf8');
  var fileLines = fileContents.split('\n');
  var LDN = fileLines[0].split(' ').map(myParseInt);
  var words = fileLines.slice(1, LDN[1] + 1);
  var patternLines = fileLines.slice(LDN[1] + 1, LDN[1] + 1 + LDN[2]);
  var patterns = patternLines.map(parsePattern);
  return {
    len: LDN[0],
    words: words,
    patterns: patterns
  };
};

var getPossibleWords = function (pattern) {
  var restPossibleWords;
  var possibleWords = [];
  var i, j;
  if (pattern.length === 1) {
    return pattern[0];
  }
  restPossibleWords = getPossibleWords(pattern.slice(1, pattern.length));
  for (i = 0; i < pattern[0].length; i += 1) {
    for (j = 0; j < restPossibleWords.length; j += 1) {
      possibleWords.push(pattern[0][i] + restPossibleWords[j]);
    }
  }
  return possibleWords;
};

var getNumWords = function (pattern, words) {
  var possibleWords = getPossibleWords(pattern);
  var numWords = 0;
  var i;
  var word;
  for (i = 0; i < possibleWords.length; i += 1) {
    word = possibleWords[i];
    if (words.indexOf(word) > -1) {
      numWords += 1;
    }
  }
  console.log('got num words for pattern');
  console.log(pattern);
  return numWords;
};

var getOutput = function(words, patterns) {
  return patterns.map(function (pattern) {
    return getNumWords(pattern, words);
  });
};

var getOutputStr = function (output) {
  var i;
  var outputStr = '';
  for (i = 0; i < output.length; i += 1) {
    outputStr += "Case #" + (i+1).toString() + ": ";
    outputStr += output[i].toString();
    outputStr += '\n';
  }
  return outputStr;
};

var input = getInput('A-small-practice.in');
var output = getOutput(input.words, input.patterns);
var outputStr = getOutputStr(output);
fs.writeFileSync('A-small-practice.out', outputStr);
