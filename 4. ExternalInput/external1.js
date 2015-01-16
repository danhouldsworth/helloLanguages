// 1. Done.

"use strict"; /* jshint
node : true
*/

var args = process.argv.slice(2); // Discard 'node' and 'filename' from the array of arguments
process.stdout.write("CLI args name is " + args[0].toUpperCase()); // Trialling a more direct access to stdout than console.log
process.stdout.write(", and age in months is " + args[1] * 12 + "\n");
