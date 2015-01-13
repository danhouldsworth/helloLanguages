// 1. Done
// 2. Done (not since revision)
// 3. Done (not since revision)
// Bonus....

'use strict'; /* jshint
node : true
*/

var http = require('http'),
    url = require('url'),
    path = require('path'),
    fs = require('fs'),
    hello2 = function (req, res) {
        var uri = url.parse(req.url).pathname.replace('/', '');
        res.writeHead(200, {'Content-Type' : 'text/html'});
        res.end('<h1>Node.js : Hello, ' + uri + '!</h1>');
    },
    hello3 = function (req, res) {
        var uri = url.parse(req.url).pathname.replace('/', ''),
            filename = path.join(process.cwd(), uri);

        fs.exists(filename, function (exists) {
            if (!exists) {
                res.writeHead(404, {'Content-Type' : 'text/plain'});
                res.write('404 Not found\n');
                res.end();
                return;
            }

            fs.readFile(filename, 'binary', function (err, file) {
                res.writeHead(200);
                res.write(file, 'binary');
                res.end();
            });
        });
    };

http.createServer(hello2).listen(8887);
http.createServer(hello3).listen(8888);
