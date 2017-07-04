"use strict";

var makeSpiral = function (N) {
  var i;
  var spiral = [];
  for (i = -N; i <= N; i += 1) {
    spiral[i] = [];
  }
  var ring;
};


var N = 5;
var sum = 0;
var cornerVals = function (N) {
  return [N*N, N*N - N + 1, N*N - 2*N + 2, N*N - 3*N + 3];
};
var i;
for (i = 1001; i >= 3; i -= 2) {
  sum += cornerVals(i).reduce(function(a,b){return a+b;});
}
console.log(sum+1);
