The real power of werkzeug is that you can create a whole hierarchy of wsgi applications, one on top of the other. These applications are known as middlewares. Each middleware performs its own
specialized task/logic and can either return a response back or delegate to a middleware lower in the hierarchy.

For example, let say we develop a website where we want to service a set of static web-pages. Then we can use a SharedDataMiddleware class which takes the path of the static web pages folder
and can present pages from there. So we can stack this middleware on top of our own wsgi application class. The HTTPServer will call this middleware first, allowing it to serve a static page if possible,
otherwise the SharedDataMiddleware will delegate to our wsgi application.

We can also have an SSOMiddleware (Single Sign On) which redirects users to a login page first for authentication and then delegates to the middleware below it in the stack.

Each middleware takes as input parameter an object of the middleware it should delegate to. We will soon see a lot of examples
