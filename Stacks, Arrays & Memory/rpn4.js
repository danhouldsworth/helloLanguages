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
                result = s1; // Add the current two for trivial case
                for (var i = 0; i <= stack.length + 2; i++) result += pull();
                break;
            // Stack operators
            case 'push':
                result = push(s1); // Put s1 back on stack as if not taken, and set as new result to be pushed
                break;
            case '<>': // Swap
                result = pull();
                push(s1);
                break;
            case '>>': // Rotate stack up
                stack.push(s1);
                result = pull(); // Negate the impending push
                break;
            case '<<': // Rotate stack down
                push(s1);
                result = stack.pop();
                break;
            default:
                result = "Invalid operator";
        }
    }
    push(result);
    process.stdout.write(stack + "]\n");
}

console.log("Answer : " + pull() );

function pull () {
    return stack.shift();
}

function push (x) {
    stack.unshift(x);
    return x;
}

function factorial (x) {
    if (x === 0 || x === 1) {return x; }
    else {return x * factorial(x - 1); }
}
