"use strict";

var _ = require('lodash');
var bn = require('bignum');

var cmpNum = function (a, b) {
  return a - b;
};

var makePrimeUtils = function () {
  var primes = [2, 3];

  var isNextPrime = function(next) {
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

  var addNextPrime = function () {
    var next = primes[primes.length-1] + 2;
    while (true) {
      if (isNextPrime(next)) {
        primes.push(next);
        return;
      }
      next += 2;
    }
  };

  return {
    isPrime: function (N) {
      var nRt = Math.sqrt(N);
      while (primes[primes.length - 1] <= nRt) {
        addNextPrime();
      }
      return isNextPrime(N);
    },
    getPrimes: function (N) {
      while (primes.length < N) {
        addNextPrime();
      }
      return primes.slice(0, N);
    },
    primesLt: function (max) {
      while (primes[primes.length - 1] < max) {
        addNextPrime();
      }
      return primes.filter(function (p) {
        return p < max;
      });
    }
  };
};

var getSubsets = function (arr, size) {
  if (size < 1 || size > arr.length) {
    throw new Error();
  }
  if (size === arr.length) {
    return [arr];
  }
  if (size === 1) {
    return arr.map(function (elem) {return [elem];});
  }
  var subsets = getSubsets(arr.slice(1), size);
  var smallerSubsets = getSubsets(arr.slice(1), size - 1);
  subsets = subsets.concat(smallerSubsets
                 .map(function (set) {
                   var setCpy = set.slice();
                   setCpy.push(arr[0]);
                   return setCpy;
                 }));
  return subsets;
};

var pu = makePrimeUtils();

var hasProp = function (pArr) {
  var pairs = getSubsets(pArr, 2);
  var i, n, m;
  for (i = 0; i < pairs.length; i += 1) {
    n = parseInt(pairs[i][0].toString()+pairs[i][1].toString());
    m = parseInt(pairs[i][1].toString()+pairs[i][0].toString());
    if (!pu.isPrime(n) || !pu.isPrime(m)) {
      return false;
    }
  }
  return true;
};



var neg = function(fn) {
  return function (x) {
    return !fn(x);
  };
};

var MAX_SUM = 26033;

var method2 = function () {
  var PRIMES = pu.primesLt(MAX_SUM);
  var ADJ_LIST = Array.apply(null, Array(PRIMES.length))
        .map(function(){return [];});
  var i, j;
  var currSet;
  for (i = 0; i < PRIMES.length - 5; i += 1) {
    currSet = PRIMES.slice(i, i + 5);
    console.log(currSet);
    if (hasProp(currSet)) {
      break;
    }
  }
};

// method2();

var method1 = function () {
  var PRIMES = pu.primesLt(MAX_SUM);

  var makeCanAdd = function (filter) {
    return function (set) {
      var REM_PRIMES = filter(set)
      // .reverse()
      ;
      var i, p;
      for (i = 0; i < REM_PRIMES.length; i += 1) {
        p = REM_PRIMES[i];
        if (hasProp(set.concat([p]))) {
          return p;
        }
      }
      return null;
    };
  };

  var filter1 = function (set) {
    return PRIMES.filter(
      function (p) {return p > set[set.length - 1];});
  };

  var filter2 = function (set) {
    var bounds = set.slice(-2).sort();
    if (bounds.length === 1) {
      bounds.splice(0, 0, 0);
    }
    var remPs = PRIMES.filter(function (p) {
      return p > bounds[0] && p < bounds[1];
    });
    if (set.length % 2 === 0) {
      remPs.reverse();
    }
    return remPs;
  };

  var canAdd = makeCanAdd(filter2);

  var j, set, toAdd, p;
  for (j = 1; j < PRIMES.length; j += 1) {
    p = PRIMES[j];
    // if (p <= 1669) {
    //   continue;
    // }
    set = [p];
    toAdd = canAdd(set);
    while (toAdd !== null) {
      set.push(toAdd);
      toAdd = canAdd(set);
      console.log(set);
      if (set.length > 4) {
        return;
      }
    }
  }

};

method1();

  //         function (set) {
  //   var REM_PRIMES = PRIMES
  //         .filter(function (p) {return p > set[set.length - 1];})
  //         // .reverse()
  //         ;
  //   var i, p;
  //   for (i = 0; i < REM_PRIMES.length; i += 1) {
  //     p = REM_PRIMES[i];
  //     if (hasProp(set.concat([p]))) {
  //       return p;
  //     }
  //   }
  //   return null;
  // };

//////////////////////////////////////
// var PRIMES = pu.primesLt(1513397);

// // var SET = [ 97, 157, 10627, 496897, 1005619];
// [ 503, 563, 1601, 429161, 438569 ]
// [ 563, 587, 7481, 120671, 344363 ]
// [ 1669, 2593, 46147, 55219, 426103 ]
// var SET = [97, 10627, 496897];
// var REM_PRIMES = PRIMES
//       .filter(function (p) {return p > SET[SET.length - 1];});

// var i, p;
// for (i = 0; i < REM_PRIMES.length; i += 1) {
//   p = REM_PRIMES[i];
//   console.log(p);
//   if (hasProp(SET.concat([p]))) {
//     break;
//   }
// }

// console.log(REM_PRIMES[REM_PRIMES.length - 1]);


////////////////////////////////////////
// var NP = 1000;
// var P_PAIRS = getSubsets(pu.getPrimes(NP).slice(1), 2);
// console.log(P_PAIRS.length);
// var pairsWProp = P_PAIRS.filter(hasProp);
// console.log(pairsWProp.length);

// var TRIPLES = getSubsets(P_PAIRS, 2)
//       .map(function (tPair) {
//         if (_.intersection(tPair[0], tPair[1]).length === 0) {
//           return null;
//         }
//         var u = _.union(tPair[0], tPair[1]);
//         if (hasProp(u)) {
//           return u;
//         }
//         return null;
//       }).filter(function(o){return o !== null;});

// console.log(TRIPLES.length);
// console.log(TRIPLES);
