"use strict";

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

var i;
var a = [];
var d;
for (i = 1; i < 10000; i += 1) {
  d = sumD(i);
  if (d !== i && sumD(d) === i) {
    a.push(i);
  }
}

console.log(a);
console.log(a.reduce(function (a,b) {return a+b;}));
