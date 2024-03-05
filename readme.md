# Client/Server, using Sockets in C
This C program allows you to send files from a client to a server. The received file on the server will be automatically tagged with a clone identifier.(By default the port will be specified as 4444 this can be changed in Api.h)

e.g:
    example_clone.png

## Usage
<pre><code>
$ make <br>
$ ./server <br>
$ ./client 127.0.0.1 example.png
</code></pre>
