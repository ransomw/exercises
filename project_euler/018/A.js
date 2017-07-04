"use strict";

var myParseInt = function (str) {
  return parseInt(str);
};

var input = "75\n95 64\n17 47 82\n18 35 87 10\n20 04 82 47 65\n19 01 23 75 03 34\n88 02 77 73 07 63 67\n99 65 04 28 06 16 70 92\n41 41 26 56 83 40 80 70 33\n41 48 72 33 47 32 37 16 94 29\n53 71 44 65 25 43 91 52 97 51 14\n70 11 33 28 77 73 17 78 39 68 17 57\n91 71 52 38 17 14 91 43 58 50 27 29 48\n63 66 04 68 89 53 67 30 73 16 69 87 40 31\n04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";

var triangle = input.split('\n')
      .map(function (line) {
        return line.split(' ').map(myParseInt);
      }).reverse();

var maxPath = Array.apply(null, Array(triangle.length))
      .map(function () {return [];});
maxPath[0] = triangle[0];
var i, j;
for (i = 1; i < triangle.length; i += 1) {
  for (j = 0; j < triangle[i].length; j += 1) {
    maxPath[i][j] = triangle[i][j] +
      Math.max(maxPath[i-1][j], maxPath[i-1][j+1]);
  }
}

console.log(maxPath[maxPath.length - 1][0]);
