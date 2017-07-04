"use strict";

var MAX_N = 28123;

var sumD = function (N) {
  var i;
  var d = [];
  for (i = 1; i < N; i += 1) {
    if (N % i === 0) {
      d.push(i);
    }
  }
  if (d.length === 0) {
    return 0;
  }
  return d.reduce(function (a,b) {return a+b;});
};

var aNums = Array.apply(null, Array(MAX_N))
      .map(function (_, i) {
        return i + 1;
      }).filter(function (N) {
        return sumD(N) > N;
      });

console.log(
Array.apply(null, Array(MAX_N))
  .map(function (_, i) {
    return i + 1;
  }).filter(function (N) {
    console.log("checking " + N);
    var i;
    for (i = 0; i < aNums.length; i += 1) {
      if (aNums[i] >= N) {
        return true;
      }
      if (aNums.indexOf(N - aNums[i]) !== -1) {
        return false;
      }
    }
    return true;
  }).reduce(function(a,b){return a+b;})
);



