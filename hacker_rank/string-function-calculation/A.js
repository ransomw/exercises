
var f1 = function(T, S) {

};

var getVal = function (str) {
  var D, iMax1, iMax2, tmp, i, remStr;
  var front, back, mid, S;
  var tried1 = [], tried2 = [];
  var maxVal;
  var Td2 = str.length / 2;
  for (D = 0; D < Td2; D += 1) {
    remStr = str.slice(D);
    iMax1 = Math.pow(str.length - D, 2)/(2*(str.length + D));
    tmp = str.length - 2*D - 1;
    iMax2 = (tmp + Math.sqrt(Math.pow(tmp, 2) - 8))/4;
    for (i = 1; i < iMax1; i += 1) {
      front = remStr.slice(0, i);
      back = remStr.slice(i, 2*i);
      if (front === back &&
          tried1.indexOf(S = front + back) === -1) {
        maxVal = Math.max(f1(str, S), maxVal);
        tried1.push(S);
      }
    }
    for (i = 1; i < iMax2; i += 1) {
      front = remStr.slice(0, i);
      tmp = remStr.slice(
        i,
        Math.ceil(i*((str.length - 2 - 2*D)/(D + i)) + i)
      ).indexOf(front);
      if (tmp !== -1) {
        S = remStr.slice(0, tmp + i);
        if (tried2.indexOf(S) === -1) {
          maxVal = Math.max(f2(str, S, i), maxVal);
          tried2.push(S);
        }
      }
    }
  }
};
