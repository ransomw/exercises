var maxSubArrSum = function (arr) {
  var maxEnd = 0;
  var maxAll = 0;
  var i;
  for (i = 0; i < arr.length; i += 1) {
    maxEnd = Math.max(0, maxEnd + arr[i]);
    maxAll = Math.max(maxAll, maxEnd);
  }
  return maxAll;
};

var getOutput = function (arr) {
  var maxSum = maxSubArrSum(arr);
  var maxNcSum;
  var arrPos = arr.filter(function (x) {return x > 0;});
  if (arrPos.length === 0) {
    maxNcSum = 0;
  } else {
    maxNcSum = arrPos.reduce(function (a,b) {return a+b;});
  }
  return maxSum+' '+maxNcSum;
};

var myParseInt = function (str) {
  return parseInt(str);
};

function processData(input) {

var inputLines = input.split('\n');
var T = parseInt(inputLines[0]);
var i;
var inputs = [];
for (i = 0; i < T; i += 1) {
  inputs.push(inputLines[2 + 2*i].split(' ').map(myParseInt));
}
inputs.map(getOutput).forEach(function (output) {
  console.log(output);
});

} 

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
