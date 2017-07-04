"use strict";

var myParseInt = function (str) {
  return parseInt(str);
};

var nCrRowGen = function (lrgMod) {
  var table = [[1], [1, 1]];
  return function (n) {
    var lastRow;
    var nextRow;
    var i;
    while (table[n] === undefined) {
      lastRow = table.slice(-1)[0];
      nextRow = [1];
      for (i = 0; i < lastRow.length - 1; i += 1) {
        nextRow.push((lastRow[i] + lastRow[i+1]) % lrgMod);
      }
      nextRow.push(1);
      table.push(nextRow);
    }
    return table[n];
  };
};

var twoPowerGen_slow = function (lrgMod) {
  var twoPowers = [1];
  return function (n) {
    while (twoPowers[n] === undefined) {
      twoPowers.push(
        (2 * twoPowers[twoPowers.length - 1]) % lrgMod
      );
    }
    return twoPowers[n];
  };
};

var twoPower = function (N, lrgMod) {
  var result = 1;
  while (N > 50) {
    result = (result * (Math.pow(2, 50) % lrgMod)) % lrgMod;
    N -= 50;
  }
  return ((Math.pow(2, N) % lrgMod) * result) % lrgMod;
};

var LRG_MOD = Math.pow(10, 9) + 7;

var nCrRow = nCrRowGen(LRG_MOD);
var twoPower_slow = twoPowerGen_slow(LRG_MOD);

var WAYS_TO_TIE = nCrRow(25+24-1)[24];

var numSeq = function (A, B) {
  var tmp;
  if (A === B) {
    return 0;
  }
  if (A > B) {
    tmp = A;
    A = B;
    B = tmp;
  }
  if (B < 25) {
    return 0;
  }
  if (B === 25) {
    if (A === 24) {
      return 0;
    }
    return nCrRow(B+A-1)[A];
  }
  if (B - A !== 2) {
    return 0;
  }
  return (WAYS_TO_TIE * twoPower(A-24, LRG_MOD)) % LRG_MOD;
};

var input = "3\n25";

var AB = input.split('\n').map(myParseInt);
console.log(numSeq(AB[0], AB[1]));
