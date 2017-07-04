"use strict";

var _ = require('lodash');

var isNextPrime = function(primes, next) {
  var nextSqrt = Math.sqrt(next);
  var i;
  for (i = 0; i < primes.length; i += 1) {
    if (primes[i] > nextSqrt) {
      return true;
    }
    if (next % primes[i] === 0) {
      return false;
    }
  }
  return true;
};

var firstPrimes = function (max) {
  var primes = [2];
  var next = 3;
  while (primes[primes.length-1] < max) {
    if (isNextPrime(primes, next)) {
      primes.push(next);
    }
    next += 2;
  }
  primes.pop();
  return primes;
};

var rDigIdxs = function (N) {
  var nDig = N.toString().split('');
  var uDig = _.unique(nDig);
  var repIdxs = [];
  if (nDig.length === uDig.length) {
    return [];
  }
  uDig.forEach(function (dig) {
    var currIdxs = nDig.map(function (d, i) {
      if (d === dig) {return i;} return null;
    }).filter(function (o) {return o !== null;});
    if (currIdxs.length > 1) {
      repIdxs.push(currIdxs);
    }
  });
  return repIdxs;
};

var getOtherDig = function (N, rdi) {
  var nDig = N.toString().split('');
  return nDig.map(function (d, i) {
    if (rdi.indexOf(i) !== -1) {return null;} return d;
  }).filter(function (o) {return o !== null;}).join('');
};

var getSubsets = function (arr) {
  if (arr.length === 1) {
    return [[], arr];
  }
  var otherSubsets = getSubsets(arr.slice(0, -1));
  return otherSubsets.concat(
    otherSubsets.map(function (ss) {
      ss = ss.slice();
      ss.push(arr[arr.length - 1]);
      return ss;
    }));
};

var N_DIG = 6;
var PRIMES = firstPrimes(Math.pow(10, N_DIG))
      .filter(function (N) {return N > Math.pow(10, N_DIG - 1);});
var PRD = {};
PRIMES.forEach(function (P) {
  var rdis = rDigIdxs(P);
  rdis.forEach(function (rdi) {
    getSubsets(rdi).filter(function(a){return a.length > 1;})
      .forEach(function (rdi) {
        var otherDig = getOtherDig(P, rdi);
        if (PRD[rdi] === undefined) {
          PRD[rdi] = {};
        }
        if (PRD[rdi][otherDig]) {
          PRD[rdi][otherDig].push(P);
        } else {
          PRD[rdi][otherDig] = [P];
        }
      });
  });
});
var maxFams = [[]];
for (var rdi in PRD) {
  for (var od in PRD[rdi]){
    if (PRD[rdi][od].length > maxFams[0].length) {
      maxFams = [PRD[rdi][od]];
    } else if (PRD[rdi][od].length === maxFams[0].length) {
      maxFams.push(PRD[rdi][od]);
    }
  }
}
console.log(maxFams);
