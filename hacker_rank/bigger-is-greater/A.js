var nextPerm = function (str) {
  var i, j;
  for (i = str.length - 2; i >= 0; i -= 1) {
    if (str[i] < str[i + 1]) {
      break;
    }
  }
  if (i === -1) {
    return 'no answer';
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

var input = "3\nab\nbb\nhefg";

var inputLines = input.split('\n');
console.log(
  inputLines.slice(1).map(nextPerm).join('\n')
);
