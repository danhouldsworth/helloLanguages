// 1. Done

"use strict"; /* jshint
node : true
*/

var n = 7,
    factorial = function (x) {
        if (x === 0 || x === 1) {return x; }
        else {return x * factorial(x - 1); }
    },
    fibb = function (x) {
        if (x === 0 || x === 1) {return x; }
        else {return fibb(x - 1) + fibb(x - 2); }
    };

for (var i = 0; i <= n; i++) {
    console.log(i + "! = " + factorial(i) + ",  \t" + i + "th Fibonacci = " + fibb(i));
}
