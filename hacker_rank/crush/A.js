var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var addBlocks = function (b1, b2) {
  return b1[2] + b2[2];
};

var sumBlocks = function (blocks) {
  var i, sum = 0;
  for (i = 0; i < blocks.length; i += 1) {
    sum += blocks[i][2];
  }
  return sum;
};

var sortedIdx = function(arr, x, cmpFn) {
  var l = 0;
  var r = arr.length - 1;
  var m;
  if (arr.length === 0) {
    return -1;
  }
  while (r - l > 1) {
    m = l + Math.floor((r - l) / 2);
    if (cmpFn(x, arr[m])) {
      l = m;
    } else {
      r = m;
    }
  }
  if (!cmpFn(x, arr[l])) {
    return -1;
  }
  if (cmpFn(x, arr[r])) {
    return r;
  }
  return l;
};

var cmpBlocksEnd = function (b1, b2) {
  return b1[1] - b2[1] >= 0;

};

var input = "5 3\n1 2 100\n2 5 100\n3 4 100";


var blocks = input.split('\n').slice(1).map(function (line) {
  return line.split(' ').map(sArg(parseInt));
});
blocks.sort(function (b1, b2) {return b1[0] - b2[0];});
var startIdx = 0, endIdx = startIdx, currSum = 0, maxSum = 0;
var currNum, currSlice, summedEndIdx;
var summedBlocks = [];
var lastIter = false;
// while (endIdx < blocks.length - 1) {
while (!lastIter) {
  currNum = blocks[startIdx][0];
  while(endIdx < blocks.length - 1 &&
        blocks[startIdx][0] === blocks[endIdx][0]) {
    endIdx += 1;
  }
  if (endIdx === blocks.length - 1 &&
      blocks[startIdx][0] === blocks[endIdx][0]) {
    lastIter = true;
  }
  summedEndIdx = 0;
  while(summedEndIdx < summedBlocks.length - 1 &&
        summedBlocks[summedEndIdx][1] < currNum) {
    summedEndIdx += 1;
  }
  currSlice = blocks.slice(startIdx, endIdx);
  currSum += sumBlocks(currSlice);
  if (summedEndIdx > 0) {
    currSum -= sumBlocks(summedBlocks.splice(0, summedEndIdx));
  }
  maxSum = Math.max(currSum, maxSum);
  currSlice.forEach(function (b) {
    summedBlocks.splice(
      sortedIdx(summedBlocks, b, cmpBlocksEnd) + 1,
      0, b);
  });
  startIdx = endIdx;
}

// process.stdout.write(maxSum.toString());
console.log(maxSum);
