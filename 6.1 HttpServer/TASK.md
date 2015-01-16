#Task

1. Listen on port 8888 for an HTTP GET request, and serve back 'Hello, world!' text with correct metadata.
2. Modify the server so 127.0.0.1:8888/hello/bananas returns 'Hello, bananas!'
3. If the request matches a file in the servers local dir then serve it, otherwise serve an appropriate 404.
4. If a GET request for /SecretAPI/password is made then have the server store and list all passwords to date.
