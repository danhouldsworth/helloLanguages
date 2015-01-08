
var n = 6;

var factorial = function(x){
    if (x === 0 || x === 1) return x;
    else return x * factorial(x - 1);
};

var fibb = function(x){
    if (x === 0 || x === 1) return x;
    else return fibb(x - 1) + fibb(x - 2);
};

var pi = function(dp){
    if (dp === 0) return 3; // No need for else as already branched

    function leibnizTerm (n){
        return Math.pow(-1, n) / (n + n + 1);
    }
    function truncate (x, precision) {
        return parseInt(x * Math.pow(10,precision) ) / Math.pow(10,precision); // Does not round
    }
    function round(decimal){
        return (decimal + 0.5) | 0; // Fast round by bitwise OR
    }

    var sum = 0.0;
    var n = 0;

    while ( truncate(sum, dp - 1) !== pi(dp - 1) ) {
        // console.log(truncate(sum, dp - 1) + " vs " + truncate(lastSum, dp));
        sum += 4 * leibnizTerm(n++);
    }

    return truncate(sum, dp);
}

for (i = 0; i <= n; i++){
    console.log(i + "! = " + factorial(i) + ",  \t" + i + "th Fibonacci = " + fibb(i) + ",   \t PI=" + pi(i) );
}
