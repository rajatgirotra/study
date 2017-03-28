/*
Let's look at many ways in which methods and properties can be exported.
*/

// Method 1. Set module.exports explicitly to the name of the function to export (greet1.js)
console.log('Method 1')
var greet1 = require ('./greet1') // javascript automatically assumes  a .js extension, so will search for greet1.js
console.log(greet1)
greet1();

// Method 2. - Set module.exports.greet property.
console.log('\n\nMethod 2');
var greet2 = require('./greet2').greet;
console.log(greet2)
greet2();

// Method 3 - Use exports instead of module.exports as a shorthand as they both refer to the same object.
console.log('\n\nMethod 3');
var m = require('./greet3');
//console.log(m); // CAREFUL, because in greet3 you set exports = "something",  javascript explicitly set a new object and module.exports always remained empty.
// This is by design. Whenever you use the equality operator on an object, a new object is created instead of modifcation to the existing one.
// So as a rule of thumb always use module.exports and dont use exports. However exports.greet = greet should work.

/* Method 4 - Use a function constructor as return an object created from that function c'tor */
console.log('\n\nMethod 4');
var greet4 = require('./greet4');
greet4.greet();
greet4.greeting = 'Goodbye Cruel World!!';
var greet4b = require('./greet4'); // requiring again will always return the cached module. So nodejs will not run your module code again, and return the same module.exports as before as it caches them.
greet4b.greet();

// Method 5- Return the function ctor itself so that you can create new objects yourself u- instead of returning the object created from the function c'tor
console.log('\n\nMethod 5');
var Greetr = require('./greet5');
var greet5a = new Greetr();
greet5a.greet();
greet5a.greeting = 'GoodBye Cruel World';
var greet5b = new Greetr();
greet5b.greet();
