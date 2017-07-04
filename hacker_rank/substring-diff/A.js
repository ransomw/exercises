"use strict";

var add = function (a, b) {
  return a + b;
};

var myMax = function (a, b) {
  return Math.max(a, b);
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
  var mData = [{len: 1, sum: seq[0]}];
  var i;
  var oneIdx, zeroIdx;
  for (i = 1; i < seq.length; i += 1) {
    if (mData[i-1].sum + seq[i] <= S) {
      mData[i] = {
        len: mData[i-1].len + 1,
        sum: mData[i-1].sum + seq[i]
      };
    } else {
      oneIdx = seq.slice(i - 1 - mData[i-1].len + 1).indexOf(1);
      mData[i] = {
        len: i - (oneIdx + 1) + 1,
        sum: mData[i-1].sum
      };
    }
  }
  return mData.map(function (o) {return o.len;}).reduce(myMax);
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
      while (hasD(seq, S, L + 1)) {
        L += 1;
      }
    }
    if (r > L) {
      seq = s1.slice(-r).split('').map(function (c, i) {
        if (c === s2[i]) {
          return 0;
        }
        return 1;
      });
      while (hasD(seq, S, L + 1)) {
        L += 1;
      }
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
