The typical way of writing your wsgi app is


class MyApp(object):
    def wsgi_app(environ, start_response):
        # Create a Request object
        request = Request(environ)
        response = Response('Hello World')
        return response(environ, start_response)

Because it is so common code, werkzeug created a wrapper on top of it using decorators. So get used to using thfe following

@Request.application
def wsgi_app(request):
    # Do whatever with request and return a response object
    return Response('Hello %s' % request.args.get('name', 'World'))

which means
wsgi_app = Request.application(wsgi_app)

# So Request.application does something like this:

class Request:
    def application(f):
        def app(environ, start_response):
            request = Request(environ)
            response = f(request)
            return response(environ, start_response)
        return app
        

If for some reason, you want to not create a request object, but deal with environ and start_response yourself, you can use the responder() wrapper.
Same as @Request.application, but does not create a Request object for you.

@responder
def wsgi_app(env, start_response):
    # Handle request and return a Response object
    return Response('Hello World')

meaning something like

def responder(f):
    def app(env, start_response):
        response = f(env, start_response)
        return response(env, start_response)
    return app


Very very trivial
    
