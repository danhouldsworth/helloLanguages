// 1. Done
// 2. Done
// 3. Done
// Bonus. Further work needed (n=7 in 3s, n=8 in 37s guessing n=10 over an hour).

"use strict"; /* jshint
node : true
*/

var n = 9,
    factorial = function (x) {
        if (x === 0 || x === 1) {return x; }
        else {return x * factorial(x - 1); }
    },
    fibb = function (x) {
        if (x === 0 || x === 1) {return x; }
        else {return fibb(x - 1) + fibb(x - 2); }
    },
    pi = function (dp) {
        if (dp === 0) {return 3; }  // No need for 'else' as already branched
        var sum = 0.0,              // Seems more elegant to break for the trivial case before declarations
            lastSum = 0.0,
            n = 0,
            leibnizTerm = function (n) {
                return Math.pow(-1, n) / (n + n + 1);
            },
            truncate = function (x, precision) {
                return parseInt(x * Math.pow(10, precision)) / Math.pow(10, precision); // Does not round
            };

        while (true) {              // Iterate until the result is the same as the previous result to n dps
            lastSum = sum;
            sum += 4 * leibnizTerm(n++);
            if (truncate(sum, dp) === truncate(lastSum, dp)) {return truncate(sum, dp); }
        }
    };

for (var i = 0; i <= n; i++) {
    console.log(i + "! = " + factorial(i) + ",  \t" + i + "th Fibonacci = " + fibb(i) + ",  \t PI=" + pi(i));
}
