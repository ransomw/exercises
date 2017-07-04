var fs = require('fs');

var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var dfs = function(adjList, start) {
  // w: white, b: black, g: grey
  var colors = Array.apply(null, Array(adjList.length))
        .map(function () {return 'w';});
  var depths = [];
  var Q = [start];
  var currV;
  colors[start] = 'g';
  depths[start] = 0;
  while(Q.length !== 0) {
    currV = Q.splice(0, 1)[0];
    adjList[currV].forEach(function (v) {
      if (colors[v] === 'w') {
        colors[v] = 'g';
        depths[v] = depths[currV] + 1;
        Q.push(v);
      }
    });
    colors[currV] = 'b';
  }
  return depths;
};

var getCompliment = function (adjList) {
  var cAdjList = [];
  adjList.forEach(function (vx, i) {
    var removeElem = function (array, elem) {
      array.splice(array.indexOf(elem), 1);
    };
    var adj = Array.apply(null, Array(adjList.length))
          .map(function (_, j) {return j;});
    removeElem(adj, i);
    vx.forEach(function (v) {
      removeElem(adj, v);
    });
    cAdjList.push(adj);
  });
  return cAdjList;
};

var getOutput = function (input) {
  return dfs(getCompliment(input.g), input.s)
    .filter(function (d) {return d !== 0;})
    .join(' ');
};

var parseInput = function (input) {
  var parsed = [];
  var i, NM, adjList;
  var inputLines = input.split('\n');
  var T = parseInt(inputLines.splice(0, 1)[0]);
  for (i = 0; i < T; i += 1) {
    NM = inputLines.splice(0, 1)[0].split(' ').map(sArg(parseInt));
    adjList = Array.apply(null, Array(NM[0]))
      .map(function () {return [];});
    inputLines.splice(0, NM[1])
      .forEach(function (line) {
        var e = line.split(' ').map(sArg(parseInt))
              .map(function (v) {return v - 1;});
        adjList[e[0]].push(e[1]);
        adjList[e[1]].push(e[0]);
      });
    parsed.push({
      g: adjList,
      s: parseInt(inputLines.splice(0, 1)[0]) - 1
    });
  }
  return parsed;
};

var input = "1\n4 2\n1 2\n1 3\n1";
input = fs.readFileSync('case5.in', 'utf8');

console.log(
  parseInput(input).map(getOutput).join('\n')
);
