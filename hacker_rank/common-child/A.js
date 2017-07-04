
var lcsLen = function (s1, s2) {
  s1 = '_' + s1;
  s2 = '_' + s2;
  var grid = [Array.apply(null, Array(s2.length))
              .map(function () {return {l:0};})];
  var i, j;
  for (i = 1; i < s1.length; i += 1) {
    grid.push([{l:0}]);
    for (j = 1; j < s2.length; j += 1) {
      if (s1[i] === s2[j]) {
        grid[i][j] = {
          l: grid[i-1][j-1].l + 1,
          d: 'diag'
        };
      } else if (grid[i - 1][j].l >= grid[i][j - 1].l) {
        grid[i][j] = {
          l: grid[i - 1][j].l,
          d: 'up'
        };
      } else {
        grid[i][j] = {
          l: grid[i][j-1].l,
          d: 'left'
        };
      }
    }
  }
  return grid[grid.length - 1][grid[0].length - 1].l;
};

var input = "SHINCHAN\nNOHARAAA";

var strs = input.split('\n');
console.log(lcsLen(strs[0], strs[1]));
