var myParseInt = function (str) {
  return parseInt(str);
};

var nCrRowGen = function (lrgMod) {
  var table = [[1], [1, 1]];
  return function (n) {
    var lastRow;
    var nextRow;
    var i;
    while (table[n] === undefined) {
      lastRow = table.slice(-1)[0];
      nextRow = [1];
      for (i = 0; i < lastRow.length - 1; i += 1) {
        nextRow.push((lastRow[i] + lastRow[i+1]) % lrgMod);
      }
      nextRow.push(1);
      table.push(nextRow);
    }
    return table[n];
  };
};

var nCrRow = nCrRowGen(Math.pow(10, 9));

var input = "2\n4\n1\n2\n3";

var inputNums = input.split('\n').map(myParseInt);
var T = inputNums.splice(0, 1);
var NK;
while(inputNums.length > 0) {
  NK = inputNums.splice(0, 2);
  console.log(nCrRow(NK[0]+NK[1]-1)[NK[1]]);
}
