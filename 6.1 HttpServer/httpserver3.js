// 3. Done

'use strict'; /* jshint
node : true
*/

var http = require('http'),
    url = require('url'),
    path = require('path'),
    fs = require('fs'),
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

http.createServer(hello3).listen(8888);
