"use strict";

var nStr = '';
var n = 0;
while (nStr.length < 1000001) {
  nStr += n;
  n += 1;
}


// console.log(nStr.length);

console.log(
Array.apply(null, Array(7)).map(
  function (_, i) {
    console.log(i);
    return parseInt(nStr[Math.pow(10, i)]);
  }).reduce(function(a,b){return a*b;})
);
