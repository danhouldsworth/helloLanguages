// 1. Done

'use strict'; /* jshint
node : true
*/

var http = require('http'),
    path = require('path'),
    hello = function (req, res) {
        res.writeHead(200, {'Content-Type' : 'text/html'});
        res.end('Hello, world!');
    };

http.createServer(hello).listen(8888);
