javascript is synchronous. It has an event loop under the hood. first when a page is loaded, an execution context is created and what all javascript code needs to be executed, it is executed by the browser. After that javascript starts looking at the event queue it has internally for any events that are happening (like mouse click, http request complete) and runs the corresponding event handler functions.

the browser just isnt running the javascript engine. it is also running the rendering engine for example of the HTTP request processor and many other smaller components. So the browser itself may be multi-threaded. But javascript itself is single threaded and runs an event loop at its core.

primitive types in javascript:

Number --> Floating point number (also used for integer arithmetic)
String --> can use double or single quotes
Boolean --> true or false

undefined --> a value which is set by default for all variables. Dont explicitly set variables to "undefined"
null --> a value which you can use to set variables to. prefer this instead of undefined.

keyword "let" --> came into ES6

can only be used in a block scope. i.e. within curly braces. and can only be used within that scope and javascript will not allow you to use a variable defined with let before it is defined to a value. with var, you can use the variables, but it is undefined
