
var n = 6;

var factorial = function(x){
    if (x === 0 || x === 1) return x;
    else return x * factorial(x - 1);
};

var fibb = function(x){
    if (x === 0 || x === 1) return x;
    else return fibb(x - 1) + fibb(x - 2);
};

for (i = 0; i <= n; i++){
    console.log(i + "! = " + factorial(i) + ",  \t" + i + "th Fibonacci = " + fibb(i) );
}
