// 1. Done.
// 2. Done.
// 3. Done.
// 4. Done.

"use strict"; /* jshint
node : true
*/

var args = process.argv.slice(2); // Discard 'node' and 'filename' from the array of arguments
process.stdout.write("CLI args name is " + args[0].toUpperCase()); // Trialling a more direct access to stdout than console.log
process.stdout.write(", and age in months is " + args[1] * 12 + "\n");

var file = require('./Library/javascript.js');
console.log("Library file name is " + file.name.toUpperCase() + ", and age in months is " + file.age * 12);

var fs = require('fs');
var configArgs = JSON.parse(fs.readFileSync('./Library/config.json')); // Don't need the non-blocking version
console.log("JSON file name is " + configArgs.name.toUpperCase() + ", and age in months is " + configArgs.age * 12);

process.stdout.write("Please enter name followed by age (seperated by space) : ");
process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', function (text) {
    args = text.split(" ");
    console.log('Name : ' + args[0].toUpperCase());
    console.log('Age in months : ' + args[1] * 12);
    process.exit();
});
