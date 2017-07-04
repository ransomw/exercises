"use strict";

var cmpNum = function (a, b) {
  return a - b;
};

var getOutput = function (nums, K) {
  var minDiff;
  var i;
  nums.sort(cmpNum);
  minDiff = nums[K - 1] - nums[0];
  for (i = 1; i + K - 1 < nums.length; i += 1) {
    minDiff = Math.min(
      minDiff,
      nums[i + K - 1] - nums[i]);
  }
  return minDiff;
};


var myParseInt = function (str) {
  return parseInt(str);
};

var processData = function (input) {
  var inputLines = input.split('\n');
  console.log(getOutput(inputLines.slice(2).map(myParseInt),
                        parseInt(inputLines[1])));
};

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
