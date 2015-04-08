// 2. Done

'use strict'; /* jshint
node : true
*/

var http = require('http'),
    url = require('url'),
    hello2 = function (req, res) {
        var uri = url.parse(req.url).pathname;
        res.writeHead(200, {'Content-Type' : 'text/html'});
        if (uri.substring(0,7) === '/hello/') {
            res.end('<h1>Node.js : Hello, ' + uri.replace('/hello/', '') + '!</h1>');
        }
        else {
            res.end('<h1>Node.js : Hello, world!</h1>');
        }
    };

http.createServer(hello2).listen(8888);
