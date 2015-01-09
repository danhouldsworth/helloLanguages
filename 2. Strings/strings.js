/*
House-keeping :
- Use ^j to check for clean code (requires Sublime + jsHint)
*/

"use strict"; /* jshint
node : true
*/

// Good habbit to have single var statement, as ensures we are clear what is in local functional scope vs global
var greeting = "The quick brown 狐 jumped over the lazy 犬",
    backwardsMsg = "";

// 1. Backwards
for (var i = 0; i < greeting.length; i++) {
    backwardsMsg += greeting[greeting.length - i - 1];
}
console.log(backwardsMsg);

// 2. Upper & Lower case
console.log(greeting.toUpperCase() + " " + greeting.toLowerCase());

// 3. Substrings
for (var i = 0; i < greeting.length; i++) {
    console.log(greeting.substring(0, i + 1));
}

/*
Learnings :
- JS strings seem to be unicode safe out of the box!
*/
