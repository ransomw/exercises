"use strict";

var fact = function (n) {
  if (n === 0) {
    return 1;
  }
  return Array.apply(null, Array(n))
    .map(function (_, i) { return i + 1; })
    .reduce(function (a,b) {return a * b;});
};

var nCrSlow = function (n, r) {
  return fact(n) / (fact(r) * fact(n - r));
};

var nCrRowGen = function () {
  var table = [[1], [1, 1]];
  return function (n) {
    var lastRow;
    var nextRow;
    var i;
    while (table[n] === undefined) {
      lastRow = table.slice(-1)[0];
      nextRow = [1];
      for (i = 0; i < lastRow.length - 1; i += 1) {
        nextRow.push(lastRow[i] + lastRow[i+1]);
      }
      nextRow.push(1);
      table.push(nextRow);
    }
    return table[n];
  };
};

var nCr = function(n, r) {
  if (r === 0) {
    return 1;
  }
  return Array.apply(null, Array(r))
    .map(function (_, i) {
      return n - r + 1 +i;
    }).reduce(function (a,b) {return a*b;}) /
    Array.apply(null, Array(r))
    .map(function (_, i) {
      return 1 + i;
    }).reduce(function (a,b) {return a*b;});
};


var nCrRow = nCrRowGen();

var myParseInt = function (str) {
  return parseInt(str);
};

var test1 = function () {
  var n, r;
  for (n = 2; n <= 1000; n += 1) {
    for (r = 0; r <= n; r += 1) {
      console.log("testing n: "+n+", r: "+r);
      if (Math.round(nCr(n, r)) !== nCrRow(n)[r]) {
        console.log("fail");
        console.log("nCrSlow: " + nCrSlow(n, r));
        console.log("nCrRow: " + nCrRow(n)[r]);
        return;
      }
    }
  }
};

test1();

// var input = "3\n2\n5\n4";

// input.split('\n').slice(1).map(myParseInt)
//   .forEach(function (n) {
//     var rowMod = nCrRow(n).map(function (i) {
//       return i % Math.pow(10, 9);
//     });
//     console.log(rowMod.join(' '));
//   });

// Array.apply(null, Array(10))
//   .map(function (_, i) {return i + 1;})
//   .forEach(function (n) {
//     console.log(nCrRow(n).join(' '));
//   });

// nCrRow(10);
// console.log('here');
// nCrRow(5);
