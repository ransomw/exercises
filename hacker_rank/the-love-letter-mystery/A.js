"use strict";

var myLog = function (str) {
  console.log(str);
};

var findCost = function (str) {
  var letters = "abcdefghijklmnopqrstuvwxyz";
  var cost = 0;
  var pLen = Math.floor(str.length / 2);
  var i;
  for (i = 0; i < pLen; i += 1) {
    cost += Math.abs(
      letters.indexOf(str[i]) -
        letters.indexOf(str[str.length - 1 - i]));
  }
  return cost;
};

var processData = function (input) {
  input.split('\n').slice(1).map(findCost).forEach(myLog);
};

process.stdin.resume();
process.stdin.setEncoding("ascii");
var _input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
