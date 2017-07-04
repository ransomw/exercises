"use strict";

var SINGLE_DIGIT = [
  null,
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"
];

var TEENS = [
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
];

var TWO_DIGIT = [
  null,
  null,
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
];

var numCharacters = function (N) {
  var num = 0;
  if (N % 100 === 0) {
    return SINGLE_DIGIT[N/100].length + "hundred".length;
  }
  if (N > 100) {
    num += SINGLE_DIGIT[Math.floor(N/100)].length +
      "hundred".length + "and".length;
  }
  N %= 100;
  if (N < 10) {
    return num + SINGLE_DIGIT[N].length;
  }
  if (N < 20) {
    return num + TEENS[N-10].length;
  }
  if (N % 10 === 0) {
    return num + TWO_DIGIT[N/10].length;
  }
  return num + TWO_DIGIT[Math.floor(N/10)].length +
    SINGLE_DIGIT[N % 10].length;
};

console.log(
  Array.apply(null, Array(999))
    .map(function (_, i) { return i + 1;})
    .map(numCharacters)
    .reduce(function (a, b) {return a+b;})
    +
    'onethousand'.length);
