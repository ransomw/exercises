
var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var getMaxCliques = function (N, M) {
  var F = (N*(N-1))/2 - M;
  if (F === 0) {
    return N;
  }
  if (F === 1) {
    return N - 1;
  }
  var guess = Math.floor((N*N)/(N+2*(F)));
  var exact = function (r) {
    var n_r = Math.floor(N/r);
    return r*(n_r*(n_r-1)/2) + n_r*(N % r);
  };
  if (exact(guess + 1) >= F) {
    console.log("HERE");
    return guess + 2;
  }
  if (exact(guess) < F) {
    throw new Error();
  }
  return guess + 1;
};

var input = "3\n3 2\n4 6\n5 7";

console.log(
  input.split('\n').slice(1)
    .map(function (line) {
      var NM = line.split(' ').map(sArg(parseInt));
      return getMaxCliques(NM[0], NM[1]);
    }).join('\n')
);
