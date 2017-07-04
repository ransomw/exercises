
var MOD = Math.pow(10, 9) + 7;

var getOutput = function (str) {
  var i, j;
  var sum = 0;
  for (i = 1; i <= str.length; i += 1) {
    for (j = 0; j <= str.length - i; j += 1) {
      sum += parseInt(str.slice(j, j+i)) % MOD;
      sum %= MOD;
    }
  }
  return sum % MOD;
};

console.log(getOutput(''));
