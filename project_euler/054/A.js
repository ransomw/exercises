"use strict";

var fs = require('fs');

var _ = require('lodash');

var cmpNum = function (a, b) {
  return a - b;
};

var VALS = [
  '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
];

var RANKS = [
  "High Card", // Highest value card.
  "One Pair", // Two cards of the same value.
  "Two Pairs", // Two different pairs.
  "Three of a Kind", // Three cards of the same value.
  "Straight", // All cards are consecutive values.
  "Flush", // All cards of the same suit.
  "Full House", // Three of a kind and a pair.
  "Four of a Kind", // Four cards of the same value.
  "Straight Flush", // All cards are consecutive values of same suit.
  "Royal Flush" // Ten, Jack, Queen, King, Ace, in same suit.
];

var cmpCards = function (ca, cb) {
  var ia = VALS.indexOf(ca[0]);
  var ib = VALS.indexOf(cb[0]);
  if (ia === -1 || ib === -1) {
    throw new Error('cmpCards failed');
  }
  return ia - ib;
};

var isFlush = function(hand) {
  return _.unique(hand.map(function (card) {
    return card[1];
  })).length === 1;
};

var isStraight = function (hand) {
  hand.sort(cmpCards);
  var valIdxs = hand.map(function (card) {
    return VALS.indexOf(card[0]);
  });
  var minIdx = valIdxs[0];
  return valIdxs.map(function (idx) {
    return idx-minIdx;
  }).join('') === '01234';
};

var partByKind = function (hand) {
  hand.sort(cmpCards);
  var part = [];
  var currKind = [];
  hand.forEach(function (card) {
    if (currKind.length === 0 ||
        currKind[0][0] === card[0]) {
      currKind.push(card);
    } else {
      part.push(currKind);
      currKind = [card];
    }
  });
  part.push(currKind);
  return part;
};

var getHandType = function (hand) {
  var flush = isFlush(hand);
  var straight = isStraight(hand);
  var kindPart = partByKind(hand);
  kindPart.sort(function(part1, part2) {
    return part1.length- part2.length;
  });
  var kindSig = kindPart
        .map(function (kind) {return kind.length;})
        .join('');
  hand.sort();
  if (flush && straight && hand[0][0] === 'T') {
    return ["Royal Flush", 'A'];
  }
  if (flush && straight) {
    return ["Straight Flush", hand[hand.length-1]];
  }
  if (kindSig === '14') {
    return ["Four of a Kind", kindPart[1][0]];
  }
  if (kindSig === '23') {
    return ["Full House", kindPart[1][0]];
  }
  if (flush) {
    return ["Flush", hand[hand.length-1]];
  }
  if (straight) {
    return ["Straight", hand[hand.length-1]];
  }
  if (kindSig === '113') {
    return ["Three of a Kind", kindPart[2][0]];
  }
  if (kindSig === '122') {
    var pairReps = [kindPart[1][0], kindPart[2][0]].sort(cmpCards);
    return ["Two Pairs", pairReps[1], pairReps[0]];
  }
  if (kindSig === '1112') {
    return ["One Pair", kindPart[3][0]];
  }
  if (partByKind(hand).length !== 5) {
    throw new Error('');
  }
  return ["High Card", hand[hand.length-1]];
};

var p1Wins = function(hand1, hand2) {
  if (hand1.length !== 5 || hand2.length !== 5) {
    throw new Error('bad args to p1 wins');
  }
  var type1 = getHandType(hand1.slice());
  var type2 = getHandType(hand2.slice());
  var rank1 = RANKS.indexOf(type1[0]);
  var rank2 = RANKS.indexOf(type2[0]);
  console.log('P1: '+type1+', P2: '+type2);
  var i, cmpRes;
  if (rank1 === -1 || rank2 === -1) {
    throw new Error();
  }
  if (rank1 > rank2) {
    return true;
  }
  if (rank1 < rank2) {
    return false;
  }
  cmpRes = cmpCards(type1[1], type2[1]);
  if (cmpRes > 0) {
    return true;
  }
  if (cmpRes < 0) {
    return false;
  }
  if (type1[2]) {
    cmpRes = cmpCards(type1[2], type2[2]);
    if (cmpRes > 0) {
      return true;
    }
    if (cmpRes < 0) {
      return false;
    }
  }
  console.log("HERE");
  hand1.sort(cmpCards);
  hand2.sort(cmpCards);
  for (i = 4; i >= 0; i -= 1) {
    cmpRes = cmpCards(hand1[i], hand2[i]);
    if (cmpRes > 0) {
      return true;
    }
    if (cmpRes < 0) {
      return false;
    }
  }
  throw new Error();
};

console.log(
  fs.readFileSync('poker.txt', 'utf8')
    .split('\n')
    .filter(function (line) {
      if (line.trim() === '') {
        return false;
      }
      var ow, tw;
      var splitLine = line.split(' ');
      ow = p1Wins(splitLine.slice(0, 5), splitLine.slice(-5));
      if (ow) {
        console.log("P1 wins");
      } else {
        console.log("P2 wins");
      }
      // tw = p1Wins(splitLine.slice(-5), splitLine.slice(0, 5));
      // if (ow === tw) {
      //   throw new Error();
      // }
      return ow;
    }).length
);
