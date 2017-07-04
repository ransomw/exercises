
var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var lis = function (seq) {
  var L = [[seq[0]]];
  var i, j, lPrev, lseq;
  for (i = 1; i < seq.length; i += 1) {
    lPrev = [];
    for (j = 0; j < i; j += 1) {
      if (L[j][L[j].length - 1] < seq[i] &&
          L[j].length > lPrev.length) {
        lPrev = L[j].slice();
      }
    }
    lPrev.push(seq[i]);
    L[i] = lPrev;
  }
  lseq = L[0];
  for (i = 1; i < L.length; i += 1) {
    if (L[i].length > lseq.length) {
      lseq = L[i].slice();
    }
  }
  return lseq;
};

var input = "5\n2\n7\n4\n3\n8";

console.log(
  lis(input.split('\n').slice(1).map(sArg(parseInt))).length
);
