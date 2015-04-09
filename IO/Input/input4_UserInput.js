// 4. Done.

"use strict"; /* jshint
node : true
*/

process.stdout.write("Please enter name followed by age (seperated by space) : ");
process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', function (text) {
    var args = text.split(" ");
    console.log('Name : ' + args[0].toUpperCase());
    console.log('Age in months : ' + args[1] * 12);
    process.exit();
});
