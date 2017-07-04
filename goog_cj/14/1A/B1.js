"use strict";

var fs = require('fs');

var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var getOutput = function (tree) {

};

var getInputs = function (input) {
  var il = input.split('\n');
  var T = parseInt(il.splice(0, 1)[0]);
  var inputs = [], N, tree;
  while (il.length > 0) {
    N = parseInt(il.splice(0, 1)[0]);
    tree = Array.apply(null, Array(N))
      .map(function () { return []; });
    il.splice(0, N - 1)
      .forEach(function (line) {
        var e = line.split(' ').map(sArg(parseInt));
        tree[e[0]-1].push(e[1]-1);
        tree[e[1]-1].push(e[0]-1);
      });
    inputs.push(tree);
  }
  return inputs;
};
