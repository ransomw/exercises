
var isFunny = function (str) {
  var S = str.split('');
  var R = str.split('').reverse();
  var sVals = S.map(function(c){return c.charCodeAt(0);});
  var rVals = R.map(function(c){return c.charCodeAt(0);});
  var i;
  for (i = 1; i < sVals.length; i += 1) {
    if (Math.abs(sVals[i] - sVals[i-1]) !==
        Math.abs(rVals[i] - rVals[i-1])) {
      return false;
    }
  }
  return true;
};

var getOutput = function (str) {
  if (isFunny(str)) {
    return 'Funny';
  }
  return 'Not Funny';
};

var input = "2\nacxz\nbcxz";

var inputLines = input.split('\n');
console.log(
  inputLines.slice(1).map(getOutput).join('\n')
);
