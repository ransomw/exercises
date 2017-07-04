"use strict";

var addChildren = function (adjList, node) {
  var childNs = adjList[node.N].filter(function (N) {
    if (node.parent !== null) {
      return N !== node.parent.N;
    } else {
      return true;
    }
  });
  node.children = childNs.map(function (N) {
    return {N: N, children: [], parent: node};
  });
  node.children.forEach(function (cNode) {
    addChildren(adjList, cNode);
  });
};

var addWeights = function(node) {
  if (node.children.length === 0) {
    node.w = 1;
    return;
  }
  node.children.forEach(function (cNode) {
    if (cNode.w === undefined) {
      addWeights(cNode);
    }
  });
  node.w = 1 +
    node.children.map(function (cNode) {return cNode.w;})
    .reduce(function (a, b) { return a + b;});
};

var makeTree = function (N, edges) {
  var adjList = Array.apply(null, Array(N+1))
        .map(function () {return [];});
  var root = {N: 1, children: [], parent: null};
  edges.forEach(function (edge) {
    adjList[edge[0]].push(edge[1]);
    adjList[edge[1]].push(edge[0]);
  });
  addChildren(adjList, root);
  addWeights(root);
  return root;
};

var countCuts = function (root) {
  var thisCuts = root.children.filter(function (node) {
    return node.w % 2 === 0;
  }).length;
  var childCuts = 0;
  if (root.children.length !== 0) {
    childCuts = root.children.map(countCuts)
      .reduce(function (a, b) { return a + b;});
  }
  return thisCuts + childCuts;
};

var myParseInt = function (str) {
  return parseInt(str);
};

var input = "10 9\n2 1\n3 1\n4 3\n5 2\n6 1\n7 2\n8 6\n9 8\n10 8";
var inputLines = input.split('\n');
var root = makeTree(parseInt(inputLines[0].split(' ')[0]),
                    inputLines.slice(1).map(function (line) {
                      return line.split(' ').map(myParseInt);
                    }));

console.log(countCuts(root));
