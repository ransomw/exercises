"use strict";

var add = function (a, b) {
  return a + b;
};

var myMax = function (a, b) {
  return Math.max(a, b);
};

var notNull = function (x) {
  return x !== null;
};

var hasD = function (seq, S, D) {
  var i;
  if (seq.length - seq.reduce(add) + S < D) {
    return false;
  }
  for (i = 0; i <= seq.length - D; i += 1) {
    if (seq.slice(i, i + D).reduce(add) <= S) {
      return true;
    }
  }
  return false;
};

var maxD = function (seq, S) {
  if (S === 0) {
    return seq.join('').split('1')
      .map(function (str) {return str.length;})
      .reduce(myMax);
  }
  if (seq.length === 1) {
    return 1;
  }
  var idxOnOne = function (x, idx) {
    if (x === 1) {
      return idx;
    }
    return null;
  }
  var midIdx = Math.floor(seq.length / 2);
  var sseq1 = seq.slice(0, midIdx).reverse();
  var sseq2 = seq.slice(midIdx);
  var oneIdxs1 = sseq1.map(idxOnOne).filter(notNull);
  var oneIdxs2 = sseq2.map(idxOnOne).filter(notNull);
  if (oneIdxs1.length + oneIdxs2.length <= S) {
    return seq.length;
  }
  var i1, i2, maxDMid = 0;
  i1 = Math.min(oneIdxs1.length, S) - 1;
  i2 = S - (i1 + 1);
  while (i1 >= 0 && i2 < oneIdxs2.length) {
    maxDMid = Math.max(
      maxDMid,
      oneIdxs1[i1] +

  }
};

var getL = function(s1, s2, S) {
  if (s1.length !== s2.length) {
    throw new Error();
  }
  var r, L = 0, seq;
  for (r = 0; r < s1.length; r += 1) {
    if (s2.length - r > L) {
      seq = s2.slice(r).split('').map(function (c, i) {
        if (c === s1[i]) {
          return 0;
        }
        return 1;
      });
      L = Math.max(L, maxD(seq, S));
    }
    if (r > L) {
      seq = s1.slice(-r).split('').map(function (c, i) {
        if (c === s2[i]) {
          return 0;
        }
        return 1;
      });
      L = Math.max(L, maxD(seq, S));
    }
  }
  return L;
};

var input = "3\n2 tabriz torino\n0 abacba abcaba\n3 helloworld yellomarin";

var inputLines = input.split('\n');
console.log(
inputLines.slice(1)
  .map(function (line) {
    var splitLine = line.split(' ');
    return getL(splitLine[1], splitLine[2], parseInt(splitLine[0]));
  }).join('\n')
);
