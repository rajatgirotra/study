You already know you can write modules in javascript. modules are re-usable pieces of code that implement some functionality.
they give you an api for using the functionality without needing to see its implementation. Now there are many different ways in which you can export and import modules.

Naive way of writing a module
=============================
var myModule = (function() {
   var privateVar = "Rajat Girotra";
   function setNameFn(newName) {
       privateVar = newName;
   }
   return { setName : setNameFn };
})(); // calling an anonymous functions which returns a javascript object with one name and value (which is a function)

// use it
myModule.setName("Vidhu Girotra");

CommonJS way
============
commonJS uses the keywords require and export to use modules. You have seen it many times already.
Example:
// Import module
var customerStore = require('store/customer');
// Export it
exports = function(){
    return customers.get('store);
}

Many such modules may exist and these are loaded synchronously - one after the other

NodeJS way
==========
// import module
var customerStore = require('store/customer'); // import module
// export it
function customerStore(){
    return customers.get('store);
}
modules.exports = customerStore;
// They are also synchronous in nature. The parameter passed to the require checks for the module name inside the node_modules directory

AMD (Asynchronous Module definition)
====================================
Similarly AMD is another way.

ES6 (EcmaScript6 or ES2015)
===========================
ES6 provides it own way.
// import it
//------ main.js ------
import { square, diag } from 'lib';
console.log(square(11)); // 121
console.log(diag(4, 3)); // 5

// export it
export const sqrt = Math.sqrt;
export function square(x) {
    return x * x;
}
export function diag(x, y) {
    return sqrt(square(x) + square(y));
}

// The express module we will import is using the ES6 way. This ensures we are using the ES6 provided Express framework.
// express is just a node framework for web development (like Django in python)

// we will create a new node project by running "npm init" in this folder. this will create a package.json for us.