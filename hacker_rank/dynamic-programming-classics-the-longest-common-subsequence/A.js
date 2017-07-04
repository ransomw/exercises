"use strict";



var lcs = function (x, y) {
  var c = [];
  var i, j;
  var seq = [];
  for (i = 0; i <= x.length; i += 1) {
    c.push([]);
  }
  for (i = 0; i <= x.length; i += 1) {
    c[i][0] = {len: 0};
  }
  for (i = 0; i <= y.length; i += 1) {
    c[0][i] = {len: 0};
  }
  for (i = 1; i <= x.length; i += 1) {
    for (j = 1; j <= y.length; j += 1) {
      if (x[i-1] === y[j-1]) {
        c[i][j] = {len: c[i-1][j-1].len + 1, dir: 'diag'};
      } else if (c[i-1][j].len >= c[i][j-1].len) {
        c[i][j] = {len: c[i-1][j].len, dir: 'up'};
      } else {
        c[i][j] = {len: c[i][j-1].len, dir: 'left'};
      }
    }
  }
  i = x.length;
  j = y.length;
  while (i > 0 && j > 0) {
    if (c[i][j].dir === 'diag') {
      seq.push(x[i-1]);
      i -= 1;
      j -= 1;
    } else if (c[i][j].dir === 'up') {
      i -= 1;
    } else {
      j -= 1;
    }
  }
  seq.reverse();
  return seq;
};


var myParseInt = function (str) {
  return parseInt(str);
};

var getInputs = function (input) {
  var inputLines = input.split('\n');
  return {
    x: inputLines[1].split(' ').map(myParseInt),
    y: inputLines[2].split(' ').map(myParseInt)
  };
};


var randInt = function (a, b) {
  return Math.floor((Math.random() * (b - a + 1))) + a;
};

// var n = randInt(1, 100);
// var m = randInt(1, 100);
// var x = Array.apply(null, Array(n)).map(
//   function () {return randInt(0, 999);});
// var y = Array.apply(null, Array(m)).map(
//   function () {return randInt(0, 999);});

// console.log(x);
// console.log(y);

// console.log(lcs(x, y).join(' '));

console.log(lcs([1, 2, 3], [1, 2]));


