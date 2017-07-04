"use strict";

var _ = require('lodash');

var getPerms = function(arr, len) {
  if (len > arr.length) {
    throw new Error();
  }
  if (len === 1) {
    return arr.map(function (elem) {
      return [elem];
    });
  }
  var i, remElems, currElem, perms = [];
  for (i = 0; i < arr.length; i += 1) {
    remElems = arr.slice();
    currElem = remElems.splice(i, 1)[0];
    perms = perms.concat(
      getPerms(remElems, len - 1)
        .map(function (perm) {
          var permCpy = perm.slice();
          permCpy.splice(0, 0, currElem);
          return permCpy;
        }));
  }
  return perms;
};

var isTri = function (N) {
  return Math.sqrt(1+8*N) % 2 === 1;
};

var isSqu = function (N) {
  return Math.sqrt(N) % 1 === 0;
};

var isPen = function (N) {
  return Math.sqrt(1+24*N) % 6 === 5;
};

var isHex = function (N) {
  return Math.sqrt(1+8*N) % 4 === 3;
};

var isHep = function (N) {
  return Math.sqrt(9+40*N) % 10 === 7;
};

var isOct = function (N) {
  return Math.sqrt(4+12*N) % 6 === 4;
};

var isFcns = [isTri, isSqu, isPen, isHex, isHep, isOct];

var satPoly0 = function (arr) {
  return arr.filter(function (elem) {
    return isFcns.filter(function (iFn) {
      return iFn(elem);
    }).length === 1;
  }).length === arr.length;
};

var satPoly1 = function (arr) {
  var isPerms = getPerms(isFcns, arr.length);
  var i;
  for (i = 0; i < isPerms.length; i += 1) {
    if (arr.map(function (elem, idx) {
      return isPerms[i][idx](elem);
    }).reduce(function(a, b) {return a && b;})) {
        return true;
    }
  }
  return false;
};


var method1 = function () {
  var a, b, c, d, e, f;
  var i, j, k, l, m, n;
  for (i = 6010; i <= 9999; i += 1) {
    a = i;
    console.log(i);
    if (!satPoly1([a]) || a.toString()[2] === '0') {
      continue;
    }
    for (j = 10; j <= 99; j += 1) {
      b = ((100*a) % 10000) + j;
      if (!satPoly1([a, b])) {
        continue;
      }
      for (k = 10; k <= 99; k += 1) {
        c = ((100*b) % 10000) + k;
        if (!satPoly1([a, b, c])) {
          continue;
        }
        for (l = 10; l <= 99; l += 1) {
          d = ((100*c) % 10000) + l;
          if (!satPoly1([a, b, c, d])) {
            continue;
          }
          for (m = 10; m <= 99; m += 1) {
            e = ((100*d) % 10000) + m;
            if (!satPoly1([a, b, c, d, e])) {
              continue;
            }
            f = ((100*e) % 10000) + Math.floor(a/100);
            if (satPoly1([a,b,c,d,e,f])) {
              console.log([a,b,c,d,e,f]);
              return;
            }
          }
        }
      }
    }
  }
};

method1();

// var SOL = [ 1024, 2415, 1520, 2016, 1680, 8037 ];

// var numSigs = SOL.map(function (N) {
//   return isFcns.map(function (fn) {return fn(N);});
// });
// numSigs.forEach(function (arr) {console.log(arr);});
// debugger;

// console.log(
// Array.apply(null, Array(9999))
//   .map(function (_, i) {return i + 1;})
//   .filter(isTri)
//   .filter(isHep)
// );

// mutually exclusive
// (tri, pen), (tri, hep), 
