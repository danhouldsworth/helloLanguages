// 1. Done. Note the use of process.stdout.write to avoid the \n appended to console.log.

"use strict"; /* jshint
node : true
*/

var greeting = "The quick brown 狐 jumped over the lazy 犬";

for (var i = 0; i < greeting.length; i++) {
    process.stdout.write(greeting[greeting.length - i - 1]);
}
console.log(greeting.toUpperCase() + " " + greeting.toLowerCase());
