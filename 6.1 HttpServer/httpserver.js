// 1. Done

var http = require('http');

http.createServer(function (req, res){
    res.writeHead(200, {'Content-Type' : 'text/html'});
    res.end("<html><h1>Hello, World!</h1></html>");
}).listen(8888);
