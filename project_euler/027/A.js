"use strict";

var isPrime = function (N) {
  var sqrtN = Math.sqrt(Math.abs(N));
  var i;
  for (i = 2; i <= sqrtN; i += 1) {
    if (N % i === 0) {
      return false;
    }
  }
  return true;
};

var getNumP = function (a, b) {
  var i = 0;
  while (isPrime(i*i + a*i + b)) {
    i += 1;
  }
  return i;
};


var maxA;
var maxB;
var maxNumP = 0;
var a, b;
var currNumP = 0;
for (a = -999; a < 1000; a += 1) {
  for (b = -999; b < 1000; b += 1) {
    console.log('a: '+a+", b: "+b+
                ', maxA: '+maxA+', maxB: '+maxB+
                'maxNumP: '+maxNumP);
    if (isPrime(b) && isPrime(currNumP*currNumP + a*currNumP + b)) {
      currNumP = getNumP(a, b);
      if (currNumP > maxNumP) {
        maxA = a;
        maxB = b;
        maxNumP = currNumP;
      }
    }
  }
}

console.log(maxA * maxB);
