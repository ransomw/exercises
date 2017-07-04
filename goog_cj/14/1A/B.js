"use strict";

var fs = require('fs');

var _ = require('lodash');

var add = function (a, b) {
  return a + b;
};

var sArg = function (fn) {
  return function (x) {
    return fn(x);
  };
};

var getOutput = function (tree) {
  var maxDepths = Array.apply(null, Array(tree.length))
        .map(function (_, i) {
          if (tree[i].length === 1) {
            return {
              d: 1, // max depth
              c: [] // child nodes of depth at least d - 1
            };
          }
          return {
            d: 2,
            c: tree[i].slice()
          };
        });
  var i, updated = true;
  var maxDepth, gdn, sdn;
  while (updated) {
    updated = false;
    for (i = 0; i < tree.length; i += 1) {
      if (tree[i].length === 1) {
        continue;
      }
      gdn = tree[i].filter(function (j) {
        return maxDepths[j].d >= maxDepths[i].d;
      }).filter(function (j) {
        return _.difference(maxDepths[j].c, [i])
          .length > 1;
      });
      if (gdn.length > 1) {
        maxDepths[i].d += 1;
        maxDepths[i].c = gdn;
        updated = true;
        continue;
      }
      sdn = tree[i].filter(function (j) {
        return maxDepths[j].d - 1 === maxDepths[i].d;
      }).filter(function (j) {
        return _.difference(maxDepths[j].c, [i])
          .length > 1;
      });
      if (_.difference(sdn, maxDepths[i].c).length > 0) {
        maxDepths[i].c = _.union(sdn, maxDepths[i].c);
        updated = true;
      }
    }
  }
  maxDepth = maxDepths.map(function(o){return o.d;})
    .reduce(function(a,b){return Math.max(a,b);});
  var nBTNodes = Array.apply(null, Array(maxDepth))
        .map(function (_, i) {return Math.pow(2, i);})
        .reduce(add);
  debugger;
  return tree.length - nBTNodes;
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

var F_NAME = 'B-sample';

var inputs = getInputs(fs.readFileSync(F_NAME+'.in', 'utf8'));
// console.log(inputs.length);

fs.writeFileSync(F_NAME+'.out',
                 inputs
                 .map(getOutput).join('\n')
                );
