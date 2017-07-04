"use strict";

var THIRTY_DAY = [9, 4, 6, 11];


var i, j;

var dfm = [0];

for (i = 0; i <= 100; i += 1) {
  for (j = 1; j <= 12; j += 1) {
    if (j === 2) {
      if (i % 4 === 0 && i !== 0) {
        dfm[dfm.length] = dfm[dfm.length-1] + 29;
      } else {
        dfm[dfm.length] = dfm[dfm.length-1] + 28;
      }
    } else if (THIRTY_DAY.indexOf(j) !== -1) {
      dfm[dfm.length] = dfm[dfm.length-1] + 30;
    } else {
      dfm[dfm.length] = dfm[dfm.length-1] + 31;
    }
  }
}

console.log(
dfm.slice(12, -1).map(function (d) {
  if (d % 7 === 6) {
    return 1;
  }
  return 0;
}).reduce(function (a, b) {return a+b;})
);
