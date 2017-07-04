
var MOD = Math.pow(10, 9) + 7;


var singleArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var calcNum = function (N, M) {
  var i;
  var num = M;
  if (N > 1) {
    num *= M - 1;
    num %= MOD;
  }
  for (i = 0; i < N - 2; i += 1) {
    num *= M - 2;
    num %= MOD;
  }
  return num;
};

var input = "2\n2 2\n2 3";

input.split('\n').slice(1)
  .map(function (line) {
    return calcNum.apply(null, line.split(' ')
                         .map(singleArg(parseInt)));
  })
  .forEach(singleArg(console.log));
