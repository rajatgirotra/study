I am straight away jumping to writing about Nodejs. May be I'll write about Javascript later or we will learn
about it along the way.

Backgroumd.

Javascript was introduced as a client side scripting language for the browser.

To process Javascript code, different companies introduced their own Javascript engines.
However, soon enough different browsers, Chrome, IE, Firefox, Safari started using these different engines
and adding their own behavior.
So all of this got standardised, and a company called ECMA standardised Javascript. So ECMAScript is the name of the standard.
ECMAScript and Javascript are sort of interchangeable words.

The new Javascript standard (2015) is called ES6 or EcmaScript 6.

Ok, now if you google, you'll find many implementation of Javascript engines used by different browsers.
One of these is called V8 javascript engine developed by Google and used by Google chrome. It is written in C++.

A very good feature of V8 is that it is embeddable and extensible. So a company called Joyent extended this V8 in the following way.
V8 allows you to define hooks which is a way of telling Javascript V8 engine that if you find this particular text, function in javascript
which is not defined in the Javascript standard (like a function, myFunction()), then call this particular function which I am defining. 

So this company called Joyent created anothter piece of software called Node (written again in C++, targeted for many different OS'es)
and created a lot of functions(hooks) , so they basically extended Javascript to give it server side capabilities.
Node core software is C++ and then they defined a bunch of Javascript functions on top of it which you can directly use.

Very easy to install and run. Just download source and do configure, make and make install.
this will install an executable called node and npm
Just say:

node app.js & it will run your javascript

Lets get going.
