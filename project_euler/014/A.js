var cNext = function (N) {
  if (N % 2 === 0) {
    return N/2;
  }
  return 3*N + 1;
};

var cSeq = function (N) {
  var seq = [N];
  while (seq.slice(-1)[0] !== 1) {
    seq.push(cNext(seq.slice(-1)[0]));
  }
  return seq;
};

var cSeqLens = function (maxLen) {
  var sLens = [undefined, 1];
  var i, j;
  var seq;
  var knownLenIdx;
  for (i = 2; i < maxLen; i += 1) {
    if (sLens[i] === undefined) {
      seq = [i];
      while (sLens[seq.slice(-1)[0]] === undefined) {
        seq.push(cNext(seq.slice(-1)[0]));
      }
      knownLenIdx = seq.pop();
      seq.reverse();
      for (j = 0; j < seq.length; j += 1) {
        sLens[seq[j]] = sLens[knownLenIdx] + j + 1;
      }
    }
  }
  return sLens;
};

var sLens = cSeqLens(1000000);
var i;
var maxLen = 0;
var maxIdx;
for (i = 1; i < 1000000; i += 1) {
  if (sLens[i] > maxLen) {
    maxLen = sLens[i];
    maxIdx = i;
  }
}

console.log(maxLen);
console.log(maxIdx);


// var i;
// for (i = 10; i < 20; i += 1) {
//   console.log(i+': '+cSeq(i));
// }
