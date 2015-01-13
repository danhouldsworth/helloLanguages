#Task

TBD

1. Listen on port 8888 for a GET request, and serve back a Hello, world! static page
2. Tailor the response to the request, so 127.0.0.1:8888/hello/bananas returns "Hello, bananas!"
3. If the request matches a file in the servers local dir then serve it, otherwise serve an appropriate 404.

Bonus. If a GET request for /SecretAPI is made then have the server return the output of ```ls -lat```
