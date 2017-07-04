var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var input = "5\n3 4 3 2 4";

var seq = input.split('\n')[1].split(' ')
      .map(sArg(parseInt)).reverse();

var E = 0;
seq.forEach(function (h) {
  E = Math.ceil((E+h)/2);
});
console.log(E);
