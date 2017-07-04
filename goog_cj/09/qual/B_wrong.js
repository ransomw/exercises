"use strict";

var fs = require('fs');

var myParseInt = function (str) {
    return parseInt(str);
};

var parseCase = function (lines) {
  var HW = lines[0].split(' ').map(myParseInt);
  var map = [];
  var height = HW[0];
  var width = HW[1];
  var i;
  for (i = 0; i < height; i += 1) {
    map.push(lines[i + 1].split(' ').map(myParseInt));
  }
  return {
    map: map,
    height: height,
    width: width
  };
};

var getInputs = function (filename) {
  var fileContents = fs.readFileSync(filename, 'utf8');
  var fileLines = fileContents.split('\n');
  var numCases = parseInt(fileLines[0]);
  var offset = 1;
  var i;
  var input = [];
  var currCase;
  for (i = 0; i < numCases; i += 1) {
    currCase = parseCase(fileLines.slice(offset, fileLines.length));
    input.push(currCase);
    offset += 1 + currCase.height;
  }
  return input;
};

var findFlowsTo = function (intMap, i, j) {
  var h = intMap[i][j];
  var N, W, E, S;
  var heights = [];
  var lowest;
  if (i === 0) {
    N = null;
  } else {
    N = intMap[i - 1][j];
    heights.push(N);
  }
  if (j === 0) {
    W = null;
  } else {
    W = intMap[i][j - 1];
    heights.push(W);
  }
  if (j === intMap[0].length - 1) {
    E = null;
  } else {
    E = intMap[i][j + 1];
    heights.push(E);
  }
  if (i === intMap.length - 1) {
    S = null;
  } else {
    S = intMap[i + 1][j];
    heights.push(S);
  }
  lowest = heights.sort()[0];
  if (h <= lowest) {
    return null;
  }
  if (lowest === N) {
    return [i - 1, j];
  }
  if (lowest === W) {
    return [i, j - 1];
  }
  if (lowest === E) {
    return [i, j + 1];
  }
  if (lowest === S) {
    return [i + 1, j];
  }
  return null;
};

var makeFlowMap = function (intMap) {
  var i, j;
  var flowMap = [];
  var flowsTo;
  for (j = 0; j < intMap.length; j += 1) {
    flowMap.push([]);
    for (i = 0; i < intMap[0].length; i += 1) {
      flowMap[j].push({flowsFrom: []});
    }
  }

  for (i = 0; i < intMap.length; i += 1) {
    for (j = 0; j < intMap[0].length; j += 1) {
      flowsTo = findFlowsTo(intMap, i, j);
      flowMap[i][j].flowsTo = flowsTo;
      if (flowsTo !== null) {
        if (flowsTo === undefined ||
            flowMap[flowsTo[0]] === undefined) {
          console.log('error');
          debugger;
        };
        flowMap[flowsTo[0]][flowsTo[1]].flowsFrom.push([i, j]);
      }
    }
  }
  return flowMap;
};

var labelBasin = function(flowMap, basinMap, start, label) {
  var inBasin = [start];
  var flowsToNextCell;
  var nextCell;
  while (inBasin.length > 0) {
    nextCell = inBasin.pop();
    basinMap[nextCell[0]][nextCell[1]] = label;
    flowsToNextCell = flowMap[nextCell[0]][nextCell[1]].flowsFrom;
    inBasin = inBasin.concat(flowsToNextCell);
  }
};

var makeBasinMap = function (flowMap) {
  var letters = 'abcdefghijklmnopqrstuvwxyz';
  var basins = [];
  var basinMap = [];
  var i, j;
  for (i = 0; i < flowMap.length; i += 1) {
    basinMap.push([]);
  }
  for (i = 0; i < flowMap.length; i += 1) {
    for (j = 0; j < flowMap[0].length; j += 1) {
      if (flowMap[i][j].flowsTo === null) {
        basins.push([i, j]);
      }
    }
  }
  for (i = 0; i < basins.length; i += 1) {
    labelBasin(flowMap, basinMap, basins[i], letters[i]);
  }
  return basinMap;
};

var makeOutputStr = function (inputs) {
  var intMaps = inputs.map(function (o) { return o.map; });
  var basinMaps = intMaps.map(makeFlowMap).map(makeBasinMap);
  var i, j;
  var outputStr = '';
  for (i = 0; i < basinMaps.length; i += 1) {
    outputStr += "Case #" + (i+1).toString() + ":\n";
    for (j = 0; j < basinMaps[i].length; j += 1) {
      outputStr += basinMaps[i][j].join(' ') + '\n';
    }
  }
  return outputStr;
};

var inputs = getInputs('B-small-practice.in');
var outputStr = makeOutputStr(inputs);
fs.writeFileSync('B-small-practice.out', outputStr);
