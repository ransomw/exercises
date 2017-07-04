"use strict";

// > String.fromCharCode(65)
// 'A'
// > ' '.charCodeAt(0)
// 32


var _ = require('lodash');

var LETTERS = 'abcdefghijklmnopqrstuvwxyz';

var getSubsets_wrong = function(arr, size) {
  if (size < 1 || size > arr.length) {
    throw new Error();
  }
  if (size === arr.length) {
    return [arr];
  }
  if (size === 1) {
    return arr.map(function (elem) {return [elem];});
  }
  console.log(arr+' '+size+' '+arr.length);
  var i, currElem, remElems;
  var subsets = [];
  for (i = 0; i < arr.length; i += 1) {
    remElems = arr.slice();
    currElem = remElems.splice(i, 1)[0];
    subsets = subsets.concat(getSubsets_wrong(remElems, size));
    subsets = subsets.concat(
      getSubsets_wrong(remElems, size - 1)
        .map(function (set) {
          var setCpy = set.slice();
          setCpy.push(currElem);
          return setCpy;
        })
    );
  }
  return subsets;
};

var SUBSETS = getSubsets_wrong([1, 2, 3], 2);
console.log(SUBSETS);
console.log(SUBSETS.length);
