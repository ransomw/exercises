"use strict";

var myParseInt = function (str) {
  return parseInt(str);
};

var intersection = function (range1, range2) {
  var tmp;
  if (range1 === null || range2 === null) {
    return null;
  }
  if (range1[0] > range2[0]) {
    tmp = range1;
    range1 = range2;
    range2 = tmp;
  }
  if (range2[0] > range1[1]) {
    return null;
  }
  return [range2[0], Math.min(range2[1], range1[1])];
};

var rLen = function (range) {
  if (range === null) {
    return 0;
  }
  return range[1] - range[0] + 1;
};

var nCyclicDoubles = function (range1, range2) {
  if (range1 === null || range2 === null) {
    return 0;
  }
  return rLen(range1) * rLen(range2) -
    rLen(intersection(range1, range2));
};

var nCyclicTriples = function (range1, range2, range3) {
  if (range1 === null || range2 === null || range3 === null) {
    return 0;
  }
  return rLen(range1) * rLen(range2) * rLen(range3) -
    nCyclicDoubles(intersection(range1, range2), range3) -
    nCyclicDoubles(range1, intersection(range2, range3)) -
    nCyclicDoubles(range2, intersection(range1, range3)) -
    rLen(intersection(range1, intersection(range2, range3)));
};

var nCyclicQuadruples = function (range1, range2, range3, range4) {
  // if (range1 === null || range2 === null ||
  //     range3 === null || range4 === null) {
  //   return 0;
  // }
  return rLen(range1) * rLen(range2) * rLen(range3) * rLen(range4) -
    nCyclicTriples(intersection(range1, range2), range3, range4) -
    nCyclicTriples(range1, intersection(range2, range3), range4) -
    nCyclicTriples(range1, range2, intersection(range3, range4)) -
    nCyclicTriples(range2, range3, intersection(range4, range1)) -
    nCyclicDoubles(intersection(range1, intersection(range2, range3)),
                   range4) -
    nCyclicDoubles(intersection(range4, intersection(range2, range3)),
                   range1) -
    nCyclicDoubles(intersection(range1, intersection(range4, range3)),
                   range2) -
    nCyclicDoubles(intersection(range1, intersection(range2, range4)),
                   range3) -
    rLen(intersection(range1,
                      intersection(range2,
                                   intersection(range3, range4))));
};

var getOutput = function (line) {
  var Rs = line.split(' ').map(myParseInt);
  var range1 = Rs.splice(0, 2);
  var range2 = Rs.splice(0, 2);
  var range3 = Rs.splice(0, 2);
  var range4 = Rs.splice(0, 2);
  return nCyclicQuadruples(range1, range2, range3, range4);
};

var input = "5\n1 4 1 3 1 2 4 4\n1 3 1 2 1 3 3 4\n1 3 3 4 2 4 1 4\n1 1 2 4 2 3 3 4\n3 3 1 2 2 3 1 2";

input.split('\n').slice(1)
  .forEach(function (line) {
    console.log(getOutput(line));
  });
