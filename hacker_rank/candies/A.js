var myParseInt = function (str) {
  return parseInt(str);
};

var getOutput = function (S) {
  var tot = 1;
  var curr = 1;
  var i;
  for (i = 1; i < S.length; i += 1) {
    if (S[i] > S[i - 1]) {
      curr += 1;
    } else {
      curr = 1;
    }
    tot += curr;
  }
  return tot;
};

var input = "3\n1\n2\n2";

console.log(getOutput(input.split('\n').map(myParseInt).slice(1)));
