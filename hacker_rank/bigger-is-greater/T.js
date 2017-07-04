var _ = require('lodash');

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

var nextPerm = function (str) {
  var i, j;
  for (i = str.length - 2; i >= 0; i -= 1) {
    if (str[i] < str[i + 1]) {
      break;
    }
  }
  if (i === -1) {
    return null;
  }
  j = i;
  for (i += 1; i < str.length; i += 1) {
    if (str[i] <= str[j]) {
      break;
    }
  }
  return str.slice(0, j) + str[i-1] +
    str.slice(i).split('').reverse().join('') +
    str[j]+
    str.slice(j + 1, i - 1).split('').reverse().join('');
};

var STR = 'abcc'.split('').sort().join('');

var l1 = _.unique(getPerms(STR.split(''))
                  .map(function (perm) {return perm.join('');})
                  .sort());
console.log("MADE l1");
l1 = l1.slice(2);
var l2 = [];
var str = l1[0];
while (str !==  null) {
  console.log(str);
  l2.push(str);
  str = nextPerm(str);
}
var i;
if (l1.length !== l2.length) {
  console.log("ERROR");
} else {
  for (i = 0; i < l1.length; i += 1) {
    console.log(l1[i] +' : '+ l2[i]);
    if (l1[i]!==l2[i]) {
      console.log("ERROR");
      break;
    }
  }
}
