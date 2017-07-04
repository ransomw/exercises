"use strict";

var isPNum = function (x) {
  return Math.sqrt(24*x+1) % 6 === 5;
};


var i = 144;
while (true) {
  if (isPNum(i*(2*i-1))) {
    break;
  }
  i += 1;
}

console.log(i*(2*i-1));
