"use strict";

var isPal = function (str) {
  var front = str.slice(0, Math.floor(str.length/2));
  var back = str.slice(Math.ceil(str.length/2));
  return front === back.split('').reverse().join('');
};

var i;
var pals = [];
for (i = 1; i < 1000000; i += 1) {
  console.log('testing '+i);
  if (isPal(i.toString()) && isPal(i.toString(2))) {
    pals.push(i);
  }
}

console.log(
  pals.reduce(function(a,b){return a+b;})
);
