"use strict";

var bn = require('bignum');

var getSeq = function (N) {

  var init = function (N) {
    return {
      a: 1,
      b: Math.floor(Math.sqrt(N))
    };
  };

  var iter = function (N, a, b) {
    var aNext = (N - b*b) / a;
    if (aNext % 1 !== 0) {
      throw new Error();
    }
    var realPart = Math.floor((Math.sqrt(N)+b)/aNext);
    var bNext = -1*(b - aNext*realPart);
    if (bNext < 0) {
      throw new Error();
    }
    return {
      a: aNext,
      b: bNext,
      ai: realPart
    };
  };

  var isRepeat = function (seq) {
    if (seq.length === 0) {
      return false;
    }
    var halfLen = seq.length / 2;
    if (halfLen % 1 !== 0) {
      return false;
    }
    var sseq1 = seq.slice(0, halfLen);
    var sseq2 = seq.slice(-halfLen);
    var i;
    for (i = 0; i < halfLen; i += 1) {
      if (sseq1[i].ai !== sseq2[i].ai ||
          sseq1[i].a !== sseq2[i].a ||
          sseq1[i].b !== sseq2[i].b) {
        return false;
      }
    }
    return true;
  };

  var currVals = init(N);
  var seq = [];
  while(!isRepeat(seq)) {
    currVals = iter(N, currVals.a, currVals.b);
    seq.push(currVals);
  }
  return seq.slice(0, seq.length/2)
    .map(function (o) {return o.ai;});
};

// given sequence and real part
// get Nth continued fraction convergent
var getConv = function (seqFn, rp, N) {
  if (N === 0) {
    return rp;
  }
  var cf = [1, seqFn(N - 1)];
  var i;
  for (i = N - 2; i >= 0; i -= 1) {
    cf = [cf[1], cf[0] + seqFn(i)*cf[1]];
  }
  return [cf[0]+rp*cf[1], cf[1]];
};

var getSeqFn = function (N) {
  var seq = getSeq(N);
  return function (i) {
    return seq[i % seq.length];
  };
};

var getPellSoln = function (D) {
  var currSeqFn, rp, rt, currConv, j;
  rt = Math.sqrt(D);
  rp = Math.floor(rt);
  currSeqFn = getSeqFn(D);
  currConv = getConv(currSeqFn, rp, 0);
  j = 1;
  while (Math.pow(currConv[0], 2) - D*Math.pow(currConv[1], 2)
         !== 1) {
    currConv = getConv(currSeqFn, rp, j);
    j += 1;
  }
  return currConv;
};

var i;
var xMax = 0, xMaxD;
var pellSoln;
for (i = 2; i <= 7; i += 1) {
  console.log(i);
  if (Math.sqrt(i) % 1 !== 0) {
    pellSoln = getPellSoln(i);

    if (currConv[0] > xMax) {
      xMax = currConv[0];
      xMaxD = i;
    }
  }
}

console.log(xMaxD);
