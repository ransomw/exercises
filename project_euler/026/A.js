"use strict";

var ordMod = function(d) {
  var p = 10;
  var o = 1;
  while (p % d !== 1) {
    p = (p * 10) % d;
    o += 1;
  }
  return o;
};

var cLen = function (d) {
  while (d % 2 === 0) {
    d /= 2;
  }
  while (d % 5 === 0) {
    d /= 5;
  }
  if (d === 1) {
    return 0;
  }
  return ordMod(d);
};

var d;
var currCLen;
var cLenMax = 0;
var dMax = [];
for (d = 2; d < 1000; d += 1) {
  currCLen = cLen(d);
  if (currCLen > cLenMax) {
    cLenMax = currCLen;
    dMax = [d];
  } else if (currCLen === cLenMax) {
    dMax.push(d);
  }
}

console.log(dMax);
