"use strict";

// > String.fromCharCode(65)
// 'A'
// > ' '.charCodeAt(0)
// 32

var fs = require('fs');
var _ = require('lodash');

var myParseInt = function (str) {
  return parseInt(str);
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

var decode = function(cipher, pass) {
  var key = pass.split('').map(function (c) {
    return c.charCodeAt(0);
  });
  return cipher.map(function (c, i) {
    return String.fromCharCode(
      c ^ key[i % key.length]
    );
  }).join('');
};

var countContains = function (arr1, arr2) {
  var count = 0;
  arr2.forEach(function (elem) {
    if (arr1.indexOf(elem) !== -1) {
      count += 1;
    }
  });
  return count;
};

var LETTERS = 'abcdefghijklmnopqrstuvwxyz';
var PASSWORDS = _.flatten(getSubsets(LETTERS.split(''), 3)
                          .map(getPerms))
      .map(function (arr) {return arr.join('');});
var CIPHER = fs.readFileSync('cipher.txt', 'utf8')
      .split(',').map(myParseInt);
var WORDS = ['the', 'be', 'to', 'of', 'and', 'in', 'that'];


var SOLNS = [];
PASSWORDS.forEach(function (pass) {
  var decoded = decode(CIPHER, pass);
  if (countContains(decoded.toLowerCase().split(/(\s+)/),
                    WORDS) > 0) {
    SOLNS.push({
      pass: pass,
      decoded: decoded,
      sum: decoded.split('').map(function (c) {
        return c.charCodeAt(0);
      }).reduce(function(a,b){return a+b;})
    });
  }
});
console.log(SOLNS);
