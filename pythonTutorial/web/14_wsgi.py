#!/usr/bin/env python

# Best part now, lets look at some of the data present in the
# environ/request object werkzeug provides a fantastic way to create
# a test environ variable from which you can create a Request
# object and use that.

from werkzeug.test import create_environ
from werkzeug.wrappers import Request


def main():
    # Create a simple environ
    # environ = create_environ('/foo', 'http://localhost:8888/')
    environ = create_environ('/foo?foo=bar', 'https://localhost:8888/')
    # make a request object out of it
    request = Request(environ)
    print('path = ', request.path)
    print('host = ', request.host)
    print('url = ', request.url)
    print('script_root = ', request.script_root)
    print('method = ', request.method)
    print('mimetype = ', request.mimetype)
    print('query_string = ', request.query_string)
    print('is_secure = ', request.is_secure)
    print('remote_addr = ', request.remote_addr)
    print('remote_user = ', request.remote_user)
    print('args = ', request.args)  # Dict of query-string arguments
    print('date = ', request.date)
    print('headers = ', request.headers)
    print('form = ', request.form)  # Dict of form data
    print('dir(request) = ', dir(request))

if __name__ == "__main__":
    main()
# If you need to set some parameters explicitly, you can also use
# Request.from_values(data=, content-length=, input_stream=,
# content-type=, method=) method by providing various arguments.


# Also it is very straightforward to handle uploads of files
def store_file(request):
    file = request.files.get('my_file')
    if file:
        file.save('/path/to/save/my_file')
    else:
        handle_error()


# Similarly you have the Response object which you can modify.
# Some important fields on Response objects are:
# response.headers --> a Dict of key and value pairs
# response.status and response.status_code -> If you set one of these,
# the other is automatically changed. So change status_code and status
# message will change automatically

# Setting a date on the response
# response.date = datetime(yyyy, mm, dd, hh, mm, ss)
# print(response.headers['Date']) prints the date

# Setting cookies
# response.set_cookie('name', 'value')
# response.headers['Set-Cookie']
