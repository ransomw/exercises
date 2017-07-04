"use strict";

var fs = require('fs');

var cmpNum = function (a, b) {
  return a - b;
};

var getTNum = function (N) {
  return (N*(N+1))/2;
};

var WORDS = fs.readFileSync('words.txt', 'utf8')
      .split(',').map(function (wq) {
        return wq.slice(1, -1);
      });
var LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
var MAX_WORD_LEN = WORDS.map(function (word) {
  return word.length;
}).sort(cmpNum).slice(-1)[0];
var MAX_WORD_VAL = MAX_WORD_LEN * 26;
var T_NUMS = [0];
while (T_NUMS[T_NUMS.length - 1] < MAX_WORD_VAL) {
  T_NUMS.push(getTNum(T_NUMS.length));
}

var isTWord = function (word) {
  var wordSum = word.split('')
        .map(function (c) {
          return LETTERS.indexOf(c) + 1;
        }).reduce(function(a,b){return a+b;});
  return T_NUMS.indexOf(wordSum) !== -1;
};

console.log(WORDS.filter(isTWord).length);
