// 1. Done
// 2. Done

'use strict'; /* jshint
node : true
*/

var http = require('http'),
    url = require('url'),
    hello = function (req, res) {
        var uri = url.parse(req.url).pathname.replace('/','');
        res.writeHead(200, {'Content-Type' : 'text/html'});
        res.end('<h1>Node.js : Hello, ' + uri + '!</h1>');
    };

http.createServer(hello).listen(8888);
