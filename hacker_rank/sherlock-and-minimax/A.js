var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var cmpNum = function (a, b) {
  return a - b;
};

// return max index of array such that x >= arr[i]
var sortedIdx = function(arr, x) {
  var l = 0;
  var r = arr.length - 1;
  var m;
  while (r - l > 1) {
    m = l + Math.floor((r - l) / 2);
    if (x >= arr[m]) {
      l = m;
    } else {
      r = m;
    }
  }
  if (arr[l] > x) {
    return -1;
  }
  if (arr[r] <= x) {
    return r;
  }
  return l;
};

var input = "3\n5 8 14\n14 16";

var inputLines = input.split('\n');
var arr = inputLines[1].split(' ').map(sArg(parseInt)).sort(cmpNum);
var P = parseInt(inputLines[2].split(' ')[0]);
var Q = parseInt(inputLines[2].split(' ')[1]);

var getMid = function (arr, i) {
  return arr[i] + Math.floor((arr[i + 1] - arr[i])/2);
};

var maxVal = 0, M, mid, rIdx, i, l;
var lIdx = sortedIdx(arr, P);
if (lIdx === -1) {
  maxVal = arr[0] - P;
  M = P;
  lIdx = 0;
} else {
  mid = getMid(arr, lIdx);
  if (P > mid) {
    lIdx += 1;
    maxVal = arr[lIdx] - P;
    M = P;
  }
}
arr = arr.slice(lIdx);
// console.log(maxVal+' : '+arr);
rIdx = sortedIdx(arr, Q);
// console.log(rIdx+' : '+arr);
if (rIdx === -1) {
  l = arr[0] - Q;
  if (l > maxVal) {
    maxVal = l;
    M = Q;
  }
} else {
  for (i = 0; i < rIdx; i += 1) {
    l = Math.floor((arr[i + 1] - arr[i])/2);
    if (l > maxVal) {
      maxVal = l;
      M = arr[i] + l;
    }
  }
  if (rIdx === arr.length - 1) {
    l = Q - arr[rIdx];
    if (l > maxVal) {
      maxVal = l;
      M = Q;
    }
  } else {
    mid = getMid(arr, rIdx);
    if (Q < mid) {
      l = Q - arr[rIdx];
      if (l > maxVal) {
        maxVal = l;
        M = Q;
      }
    } else {
      i = rIdx;
      l = Math.floor((arr[i + 1] - arr[i])/2);
      if (l > maxVal) {
        maxVal = l;
        M = arr[i] + l;
      }
    }
  }
}

console.log(M);
console.log(maxVal);
