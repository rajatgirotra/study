/*
In nodejs, you can build modules. A module is a set of functions in Javascript which can be included in your nodejs (using require function) without the risk of
names colliding with any other functions in your javascript and functions from other modules.
Kind of namespace like in C++.

See greet.js which is a very simple module. does nothing but log a string
*/

require('./greet.js'); // this will execute all statements in greet.js which are in the global execution context.

// But note greet.js has a function greet which if you try to call here will result in an error
greet(); //This is by design, if you want to use greet function, you'll have to modify you module to export it using module.exports (we'll later)
