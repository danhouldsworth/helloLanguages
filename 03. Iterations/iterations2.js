// 2. Done
// Bonus. Further work needed (n=7 in 3s, n=8 in 37s, n=9 in 769s guessing n=10 several hours). I can get down to 200secs for n=9 by calcing 10^dp terms before checking.

"use strict"; /* jshint
node : true
*/

var n = 7,
    pi = function (dp) {
        var sum = 0.0,
            lastSum = 0.0,
            n = 0,
            leibnizTerm = function (n) {
                return Math.pow(-1, n) / (n + n + 1);
            },
            truncate = function (x, precision) {
                return parseInt(x * Math.pow(10, precision)) / Math.pow(10, precision); // Does not round
            };

        while (true) {
            lastSum = truncate(sum, dp);
            sum += 4 * leibnizTerm(n++);
            if (truncate(sum, dp) === lastSum) {return lastSum; }
            // Return the current term if it didn't change to dp decimal places (irrespective of pi(dp-1))
        }
    };

console.log("PI (to " + n + " dp's) = " + pi(n));
