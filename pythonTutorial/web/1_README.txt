There are multiple python libraries needed to built a webapp.

Basically you need to

1) Know what is WSGI (Web server gateway interface) and the python standard module wsgiref.
2) Know about werkseug library which provides an HTTPServer and WSGI implementation.
3) Know about a template rendering implementation like Ninja, Django
4) Know about WTForms which is an implementation for managing Form data for HTTP Post.
5) Know about Flask which wraps werkseug and Ninja

We'll start with WTForms.
