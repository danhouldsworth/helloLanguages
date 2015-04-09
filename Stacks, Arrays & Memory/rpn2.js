// 2. Done.

"use strict"; /* jshint
node : true
*/

var rpnCommands = process.argv[2].split(" ");
console.log("Task : " + rpnCommands);

var stack = [];

for (var i = 0; i < rpnCommands.length; i++){

    var thisCommand = rpnCommands[i];
    if (thisCommand === 'e')  thisCommand = 2.71828182846;
    if (thisCommand === 'pi') thisCommand = 3.14159265359;

    var numericValue = parseFloat(thisCommand);

    process.stdout.write(thisCommand + " : [");

    if (isNaN(numericValue)) { // Assume 2 value operator
        var s1 = stack.shift();
        var s2 = stack.shift();
        switch (thisCommand) {
            case '+':
                stack.unshift(s2 + s1);
                break;
            case '-':
                stack.unshift(s2 - s1);
                break;
            case '*':
                stack.unshift(s2 * s1);
                break;
            case '/':
                stack.unshift(s2 / s1);
                break;
        }
    } else {
        stack.unshift(numericValue);
    }
    process.stdout.write(stack + "]\n");
}

console.log("Answer : " + stack.shift() );

