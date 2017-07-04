"use strict";

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

var i, cSeq, nOdd = 0;
for (i = 2; i <= 10000; i += 1) {
  if (Math.sqrt(i) % 1 !== 0) {
    cSeq = getSeq(i);
    if (cSeq.length % 2 === 1) {
      nOdd += 1;
    }
  }
}

console.log(nOdd);
