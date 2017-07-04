"use strict";

var _ = require('lodash');

var i, j;
var P_NUMS = [];
for (i = 0; i < 100000; i += 1) {
  P_NUMS.push((i*(3*i-1))/2);
}
var MAX_IDX = _.sortedIndex(P_NUMS, P_NUMS[P_NUMS.length - 1] / 2);

var minDiff = P_NUMS[P_NUMS.length - 1];
var diff, sum;
for (i = 1; i < MAX_IDX; i += 1) {
  console.log(i);
  for (j = 1; j <= MAX_IDX - i; j += 1) {
    sum = P_NUMS[j + i] + P_NUMS[j];
    diff = P_NUMS[j + i] - P_NUMS[j];
    if (diff > minDiff) {
      break;
    }
    if (P_NUMS.indexOf(sum) !== -1 &&
        P_NUMS.indexOf(diff) !== -1 &&
        diff < minDiff
       ) {
         minDiff = diff;
         console.log(minDiff);
       }
    }
}

console.log(minDiff);
