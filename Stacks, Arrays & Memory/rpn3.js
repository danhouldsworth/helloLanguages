// 3. Done.

"use strict"; /* jshint
node : true
*/

var rpnCommands = process.argv[2].split(" ");
console.log("Task : " + rpnCommands);

var stack = [];

while (rpnCommands.length > 0){

    var thisCommand = rpnCommands.shift();
    if (thisCommand === 'e')  thisCommand = Math.E;
    if (thisCommand === 'pi') thisCommand = Math.PI;

    var result = parseFloat(thisCommand);

    process.stdout.write(thisCommand + " : [");

    if (isNaN(result)) {
        var s1 = pull();
        switch (thisCommand) {
            // Double value operators....
            case '+':
                result = pull() + s1;
                break;
            case '-':
                result = pull() - s1;
                break;
            case '*':
                result = pull() * s1;
                break;
            case '/':
                result = pull() / s1;
                break;
            case '^':
                result = Math.pow(pull(), s1);
                break;
            // Single value operators....
            case 'sin':
                result = Math.sin(s1);
                break;
            case 'cos':
                result = Math.cos(s1);
                break;
            case 'ln':
                result = Math.log(s1);
                break;
            case '!':
                result = factorial(s1);
                break;
            // Full stack operators... (more of a macro)
            case 'sum':
                result = pull() + s1; // Add the current two for trivial case
                for (var i = 0; i < stack.length; i++) rpnCommands.unshift('+');
                break;
            default:
                result = "Invalid operator";
        }
    }
    push(result);
    process.stdout.write(stack + "]\n");
}

console.log("Answer : " + pull() );

function pull (x) {
    return stack.shift();
}

function push (x) {
    return stack.unshift(x);
}

function factorial (x) {
    if (x === 0 || x === 1) {return x; }
    else {return x * factorial(x - 1); }
}
