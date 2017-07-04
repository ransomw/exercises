"use strict";

var _ = require('lodash');

var cmpNum = function (a, b) {
  return a - b;
};

var myMin = function (a, b) {
  return Math.min(a, b);
};

var notNull = function (x) {
  return x !== null;
};

var range = function (a, b) {
  if (b === undefined) {
    b = a;
    a = 0;
  }
  if (b < a) {
    throw new Error();
  }
  return Array.apply(null, Array(b-a))
    .map(function (_, i) { return i + a; });
};

var getSubsets = function (arr, size) {
  if (size < 1 || size > arr.length) {
    throw new Error();
  }
  if (size === arr.length) {
    return [arr];
  }
  if (size === 1) {
    return arr.map(function (elem) {return [elem];});
  }
  var subsets = getSubsets(arr.slice(1), size);
  var smallerSubsets = getSubsets(arr.slice(1), size - 1);
  subsets = subsets.concat(smallerSubsets
                 .map(function (set) {
                   var setCpy = set.slice();
                   setCpy.push(arr[0]);
                   return setCpy;
                 }));
  return subsets;
};

var getPerms = function (arr) {
  var i, currElem, remElems;
  var perms = [];
  if (arr.length === 1) {
    return [arr];
  }
  for (i = 0; i < arr.length; i += 1) {
    remElems = arr.slice();
    currElem = remElems.splice(i, 1)[0];
    perms = perms.concat(
      getPerms(remElems).map(function (perm) {
        var permCpy = perm.slice();
        permCpy.push(currElem);
        return permCpy;
      }));
  }
  return perms;
};

var NUMS = range(1, 11);

var innerCircles = _.flatten(
  getSubsets(NUMS.slice(0, -1), 5)
    .map(function (set) {
      return getPerms(set.slice(1))
        .map(function (perm) {
          perm = perm.slice();
          perm.push(set[0]);
          return perm;
        });
    })
);

var getGonTotal = function (innerCircle) {
  var outerSet = _.difference(NUMS, innerCircle).sort(cmpNum);
  var innerSums = innerCircle.map(function (x, i) {
    return x + innerCircle[(i+1) % innerCircle.length];
  }).sort(cmpNum).reverse();
  var sums = _.unique(
    _.zip(outerSet, innerSums).map(function (pair) {
      return pair[0] + pair[1];
    })
  );
  if (sums.length > 1) {
    return null;
  }
  return sums[0];
};

var getOuterCircle = function (innerCircle) {
  var gonTot = getGonTotal(innerCircle);
  var circle = [], i;
  if (gonTot === null) {
    return null;
  }
  for (i = 0; i < innerCircle.length; i += 1) {
    circle.push(gonTot - (innerCircle[i] +
                          innerCircle[(i+1) % innerCircle.length]));
  }
  return circle;
};

var getGonSig = function (iC) {
  var oC = getOuterCircle(iC);
  var sIdx, i, sig = '';
  if (oC === null) {
    return null;
  }
  sIdx = oC.indexOf(oC.reduce(myMin));
  for (i = 0; i < oC.length; i += 1) {
    sig += oC[(sIdx + i) % oC.length].toString() +
      iC[(sIdx + i) % iC.length].toString() +
      iC[(sIdx + 1 + i) % iC.length].toString();
  }
  return sig;
};

// console.log(
//   innerCircles.map(getOuterCircle)
//     .filter(notNull)
//   );


console.log(
  innerCircles.map(getGonSig)
    .filter(notNull)
    .sort()
    .reverse()
    .join('\n')
);
