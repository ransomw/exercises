"use strict";

var checkProp = function (N) {
  var nStr = N.toString();
  var divs = [2, 3, 5, 7, 11, 13, 17];
  var i;
  for (i = 1; i <= 7; i += 1) {
    if (parseInt(nStr.slice(i, i+3)) % divs[i-1] !== 0) {
      return false;
    }
  }
  return true;
};

var getPerms = function(arr) {
  var perms = [];
  var arrCopy, arrElem;
  var i;
  if (arr.length === 1) {
    return [arr];
  }
  for (i = 0; i < arr.length; i += 1) {
    arrCopy = arr.slice();
    arrElem = arrCopy.splice(i, 1)[0];
    perms = perms.concat(
      getPerms(arrCopy).map(function (perm) {
        perm.push(arrElem);
        return perm;
      })
    );
  }
  return perms;
};

console.log(
getPerms([0, 1, 2, 3, 4, 6, 7, 8, 9])
  .map(function (perm) {
    perm.splice(5, 0, 5);
    return perm;
  })
  .map(function (panDs) {
    return parseInt(panDs
                    .map(function(d){return d.toString();}).join(''));
  }).filter(checkProp).reduce(function(a,b){return a+b;})
);
