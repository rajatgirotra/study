There are many ways you can implement HTTP client and servers with Boost.

1) Primitive way is that we ourselves build the HTTP request and manually parse the responses.
2) The other better way is to use Boost.Beast which builds on top of Boost.Asio and provides support for a lot of HTTP and websockets boilerplate code.

Also remember that when you write an HTTP server, you must use boost asio signals to handle SIGQUIT/SIGTERM/SIGSTOP etc and close the socket and stop the io_context
for a graceful shutdown.

Lets write an HTTP async client to read a static web page.