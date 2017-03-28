#!/usr/bin/env python
from werkzeug.wrappers import Request, Response
from werkzeug.utils import redirect
from werkzeug.routing import Map, Rule
from werkzeug.exceptions import HTTPException, NotFound
from werkzeug.serving import run_simple
from werkzeug.wsgi import SharedDataMiddleware

# lets now define our application class and use request and response objects

class MyApp(object):

    def dispatch_request(self, request):
        # Create a werkzeug response object
        response = Response('<h1>Hello Werkzeug</h1>', mimetype='text/html')
        return response

    def myApp(self, env, start_response):
        # Create a request object
        request = Request(env)
        response = self.dispatch_request(request)
        return response(env, start_response)

    def __call__(self, env, start_response):
        return self.myApp(env, start_response)


def create_app():
    app = MyApp()
    return app


def main():
    # Host, port
    run_simple('127.0.0.1', 8888, create_app(), use_debugger=True,
               use_reloader=True)

if __name__ == "__main__":
    main()

# Load this in your browser http://127.0.0.1:8888/
# Lets see what is happening here

# 1) We are creating a class with __call__ and handling the class object to run_simple()
#    so the HTTPServer can call our class with env and start_response parameters
# 2) Then we delegate to myApp function. The myApp function creates a Request object and hands over the request to handle_request.
#    Note as you saw in 8_wsgi.py, someone will need to call start_response callable which HTTPServer provides you. That responsibility
#    is taken by the Response object of werkzeug.
# 3) in handle_request we create a response object with the data and the mimetype. By default, mimetype is text/plain.
# 4) we return the response object back. Note that the response object itself is a WSGI app. meaning that it takes an env, and start_response parameter
# 5) we finally call the response callable and result is sent back to server
