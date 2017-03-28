#!/usr/bin/env python
from werkzeug.wrappers import Request, Response
from werkzeug.utils import redirect
from werkzeug.routing import Map, Rule
from werkzeug.exceptions import HTTPException, NotFound
from werkzeug.serving import run_simple
from werkzeug.wsgi import SharedDataMiddleware


def myApp(env, start_response):
    start_response('200 OK', [('Content-Type', 'text/html')])
    return ['<h1>Hello World</h1>']


def main():
    # Host, port
    run_simple('127.0.0.1', 8888, myApp, use_debugger=True, use_reloader=True)

if __name__ == "__main__":
    main()

# Load this in your browser http://127.0.0.1:8888/
# use_reloader will detect changes to your sources and will restart your app automatically
