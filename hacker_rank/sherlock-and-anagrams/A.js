
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
  console.log(str1+' : '+str2);
  return true;
};

var numAnaPairs = function (str) {
  var d, i, j, num = 0;
  for (d = Math.floor(str.length/2); d > 0; d -= 1) {
    for (i = d; i <= str.length - d; i += 1) {
      for (j = i; j <= str.length - d; j += 1) {
        if (isAnaPair(str.slice(i-d, i), str.slice(j, j+d))) {
          num += 1;
        }
      }
    }
  }
  return num;
};


var input = "2\nabba\nabcd";

var inputLines = input.split('\n');
console.log(
  inputLines.slice(1).map(numAnaPairs).join('\n')
);
