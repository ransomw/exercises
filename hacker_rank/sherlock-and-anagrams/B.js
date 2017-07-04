var isAnaPair = function (str1, str2) {
  if (str1.length !== str2.length) {
    throw new Error();
  }
  var ss1 = str1.split('').sort();
  var ss2 = str2.split('').sort();
  var i;
  for (i = 0; i < ss1.length; i += 1) {
    if (ss1[i] !== ss2[i]) {
      return false;
    }
  }
  return true;
};

var isPairInList = function (list, pair) {
  var i;
  for (i = 0; i < list.length; i += 1) {
    if ((list[i][0] === pair[0] && list[i][1] === pair[1]) ||
        (list[i][0] === pair[1] && list[i][1] === pair[0])) {
      return true;
    }
  }
  return false;
};

var numAnaPairs = function (str) {
  var d, i, j, num = 0, pairs = {}, ss1, ss2, ss;
  for (d = 1; d < str.length; d += 1) {
    for (i = 0; i < str.length - d; i += 1) {
      ss1 = str.slice(i, i+d);
      for (j = i + 1; j <= str.length - d; j += 1) {
        ss2 = str.slice(j, j + d);
        if (isAnaPair(ss1, ss2)) {
          ss = ss1.split('').sort().join('');
          if (pairs[ss]) {
            if (!isPairInList(pairs[ss], [ss1, ss2])) {
              pairs[ss].push([ss1, ss2]);
            }
          } else {
            pairs[ss] = [[ss1, ss2]];
          }
        }
      }
    }
  }
  for (ss in pairs) {
    console.log(pairs[ss]);
    num += pairs[ss].length;
  }
  return num;
};

var input = "1\nabab";

var inputLines = input.split('\n');
console.log(
  inputLines.slice(1).map(numAnaPairs).join('\n')
);
