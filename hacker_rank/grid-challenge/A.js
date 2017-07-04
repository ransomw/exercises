

var getCases = function (input) {
  var inputLines = input.split('\n');
  var T = parseInt(inputLines.splice(0,1)[0]);
  var N;
  var cases = [];
  while (inputLines.length > 0) {
    N = parseInt(inputLines.splice(0,1)[0]);;
    cases.push(inputLines.splice(0, N)
               .map(function (line) {return line.split('');}));
  }
  return cases;
};

var getCols = function (mat) {
  var cols = Array.apply(null, Array(mat[0].length))
        .map(function () { return []; });
  var i, j;
  for (i = 0; i < mat.length; i += 1) {
    for (j = 0; j < mat[0].length; j += 1) {
      cols[j][i] = mat[i][j];
    }
  }
  return cols;
};

var isSorted = function (arr) {
  var i;
  for (i = 1; i < arr.length; i += 1) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
};

var getResult = function (grid) {
  grid.forEach(function (row) { row.sort(); });
  if (getCols(grid).map(isSorted).indexOf(false) === -1) {
    return "YES";
  }
  return "NO";
};

var input = "2\n5\nebacd\nfghij\nolmkn\ntrpqs\nxywuv\n5\nebacd\nfghij\nolmkn\ntrpqs\nxywuv";

getCases(input).map(getResult).forEach(
  function (result) {
    console.log(result);
  });


