
var input = "5\n8 1\n4 2\n5 6\n3 1\n4 3";
console.log(
input.split('\n').slice(1)
      .map(function (line, i) {
        var splitLine = line.split(' ');
        return {
          t: parseInt(splitLine[0]) + parseInt(splitLine[1]),
          i: i + 1
        };
      }).sort(function (a, b) {
        return a.t - b.t;
      }).map(function (o) {return o.i;}).join(' ')
);
