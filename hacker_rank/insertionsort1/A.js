var myParseInt = function (str) {
    return parseInt(str);
};

function processData(input) {
    var arr = input.split('\n')[1].split(' ').map(myParseInt);
    var i;
    var V = arr[arr.length - 1];
    for (i = arr.length - 2; i >= 0; i -= 1) {
        if (arr[i] > V) {
            arr[i+1] = arr[i];
            console.log(arr.join(' '));
        } else {
            break;
        }
    }
    arr[i+1] = V;
    console.log(arr.join(' '));
}

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
