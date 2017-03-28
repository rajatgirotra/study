Lets study about werkseug library and WSGI

WSGI is Web service gateway interface. It is a specification/protocol on how a web server (Httpserver) and a web_application (like a python app) should communicate.
Very simple protocol. The web_application is called with two arguments:

def handle_web_request(environ, start_response):
where
1) environ encapsulates everything about the request; like URL, HTTP Headers, parameters, query string, form data etc.
2) start_response callable. This is a function which you can populate and then add data which is sent back.

Let's see it in action and how werkeug provides a wrapper and other services for simplying developing web-apps
