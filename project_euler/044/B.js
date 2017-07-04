var isPNum = function (x) {
  return Math.sqrt(24*x+1) % 6 === 5;
};

var i, j;
var P_NUMS = [];
for (i = 1; i < 3000; i += 1) {
  P_NUMS.push((i*(3*i-1))/2);
}

var P_PAIRS = [];
var p1, p2;
for (i = 0; i < P_NUMS.length; i += 1) {
  for (j = i + 1; j < P_NUMS.length; j += 1) {
    p1 = P_NUMS[i];
    p2 = P_NUMS[j];
    P_PAIRS.push([p1, p2]);
  }
}

console.log(
  P_PAIRS.filter(function (pair) {
    return isPNum(pair[0]+pair[1]);
  }).filter(function (pair) {
    return isPNum(pair[0]+2*pair[1]);
  })
);
