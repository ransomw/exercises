var myParseInt = function (str) {
  return parseInt(str);
};



var input = "4 2\n0 1\n2 3";

var inputLines = input.split('\n');
var N = parseInt(inputLines[0].split(' '));
var countries = Array.apply(null, Array(N))
      .map(function (_, i) {
        return [i];
      });
inputLines.slice(1)
  .forEach(function (line) {
    var a = parseInt(line.split(' ')[0]);
    var b = parseInt(line.split(' ')[1]);
    var i, ia, ib, ca, cb, tmp;
    for (i = 0; i < countries.length; i += 1) {
      if (countries[i].indexOf(a) !== -1) {
        ia = i;
      }
      if (countries[i].indexOf(b) !== -1) {
        ib = i;
      }
    }
    if (ia !== ib) {
      if (ia < ib) {
        tmp = 1;
      } else {
        tmp = 0;
      }
      ca = countries.splice(ia, 1)[0];
      cb = countries.splice(ib - tmp, 1)[0];
      countries.push(ca.concat(cb));
    }
  });
console.log(
  ((N*(N-1))/2) -
    countries.map(function (arr) {return arr.length;})
    .map(function (N) {return (N*(N-1))/2;})
    .reduce(function (a, b) {return a+b;}));
