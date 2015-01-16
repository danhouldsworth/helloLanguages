// 3. Done.

"use strict"; /* jshint
node : true
*/

var fs = require('fs');
var configArgs = JSON.parse(fs.readFileSync('./Library/config.json')); // Don't need the non-blocking version
console.log("JSON file name is " + configArgs.name.toUpperCase() + ", and age in months is " + configArgs.age * 12);
