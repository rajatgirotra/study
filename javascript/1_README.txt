About javascript
================

you write javascript code in *.js files. When the javascript interpreter starts executing your code, it creates something called as the global execution context. Also it creates a global object and a variable "this" which points to the global object. When javascript code is executed in browser, this global object is the "window" object. So "window" and "this" both refer to the same object. When javascript engine runs elsewhere (not in the browser), even then it creates a global execution object, some other global object and the "this" variable pointing to the global object.

Also the execution environment has a reference to the outer environment. when one function calls another, two execution contexts will be created on a stack (just like a normal function stack). Each execution context is first created (i.e. memory is allocated for all its variables and functions), and then the code is executed in that context.

the execution context goes through two phases
1) creation phase
in this phase, the interpreter/compiler goes through the code javascript code and creates raw memory for the variables and functions in your code.
All the variables are initially set to "undefined". undefined is a special value for an javascript object (a javascript object is a name and value pair)

2) the execution phase
in this phase your code is executed.

Say you have the following javascript code:
---------------------------------
function b() {
    console.log('called b!');
}

b();

console.log(a);

var a = 'Hello World';

console.log(a);
---------------------------------

the output will be

called b!
undefined
Hello World

note that a is declared after the first console.log(a) call but it prints undefined. That's because the execution context has already been created.

Also javascript is single threaded and synchronous. that means at any time only a single javascript line is getting executed. that means at any time only a single javascript line is getting executed. the javascript engine runs an event loop and if there is any event to process like onClick(), etc its processed on the event loop after all execution contexts have finished executing.

Also all variables and functions declared in the global execution context become part of the global "window" object.
you can see that next in app1.js

see js_tutorial/app1.js/app2.js next
