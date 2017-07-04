var myParseInt = function (str) {
  return parseInt(str);
};


var input ="5 1\n4 2 3 5 1";

var inputLines = input.split('\n');
var K = parseInt(inputLines[0].split(' ')[1]);
var i;
var currPerm = inputLines[1].split(' ').map(myParseInt);
var remSwaps = K;
var tmp, idx;

for (i = currPerm.length; i > 0; i -= 1) {
  if (remSwaps === 0) {
    break;
  }
  idx = currPerm.indexOf(i);
  if (idx !== currPerm.length - i) {
    currPerm[idx] = currPerm[currPerm.length - i];
    currPerm[currPerm.length - i] = i;
    remSwaps -= 1;
  }
}

console.log(currPerm.join(' '));
