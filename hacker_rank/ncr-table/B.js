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

var myParseInt = function (str) {
  return parseInt(str);
};


function processData(input) {


input.split('\n').slice(1).map(myParseInt)
  .forEach(function (n) {
  //  var rowMod = nCrRow(n).map(function (i) {
  //    return i % Math.pow(10, 9);
  //  });
    console.log(nCrRow(n).join(' '));
  });


}

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
