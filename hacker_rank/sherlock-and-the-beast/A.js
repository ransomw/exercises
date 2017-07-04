"use strict";

var largestDecentNumber = function (N) {
  var i;
  var n5 = undefined;
  var n3 = undefined;
  var threes;
  var fives;
  var NO = [1, 2, 4, 7];
  if (NO.indexOf(N) !== -1) {
    return -1;
  }
  for (i = 0; i < 3; i += 1) {
    if ((N - i*5) % 3 === 0) {
      n3 = i*5;
      n5 = N - i*5;
      return Array(n5+1).join('5') + Array(n3+1).join('3');
    }
  }
  throw new Error("unexpected");
};



var range = Array.apply(null, Array(11))
      .map(function(_, i) { return i + 1;});



// console.log(range.map(largestDecentNumber));
            // .filter(function (res) {
            // return res.n5 < 0;}));
