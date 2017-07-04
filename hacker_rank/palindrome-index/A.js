var isPal = function (str) {
  var front = str.slice(0, Math.floor(str.length/2));
  var back = str.slice(Math.ceil(str.length/2));
  return front === back.split('').reverse().join('');
};

var findPalIdx = function (str) {
  var i, bi;
  var pLen = Math.floor(str.length / 2);
  for (i = 0; i < pLen; i += 1) {
    bi = str.length - i - 1;
    if (str[i] !== str[bi]) {
      if (isPal(str.slice(i+1, bi+1))) {
        return i;
      }
      return bi;
    }
  }
  return -1;
};

var input = "1\nabcdedcbaz";

var inputLines = input.split('\n');
console.log(
  inputLines.slice(1).map(findPalIdx).join('\n')
);
