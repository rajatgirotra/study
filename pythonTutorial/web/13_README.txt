Lets talk about Exceptions

In werkseug, exceptions also are WSGI applications. So you can simply return them from your function

try:
  # Code
except HTTPException as e:
    return e


A number of exceptions already exist like werkzeug.exceptions

1) Unauthorized
2) HTTPException
3) Forbidden
4) BadRequest
5) NotFound
6) etc etc. Look at docs
------------------------------------------------------------------
You can also call the abort() function with the error code instead of returning the Exception class. Both are same and a matter of convenience

from werkzeug.exceptions import abort, NotFund

abort(404) or
return NotFound()

are same.
------------------------------------------------------------------

If there is a need ever, look into the exceptions module to create your own custom exception.

class MyException(HTTPException):
    code = 402
    description = '<p>Payment required.</p'
    
------------------------------------------------------------------
