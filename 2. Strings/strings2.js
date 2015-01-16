// 2. Done

"use strict"; /* jshint
node : true
*/

var greeting = "The quick brown 狐 jumped over the lazy 犬";

for (var i = 0; i < greeting.length; i++) {
    console.log(greeting.substring(0, i + 1));
}

