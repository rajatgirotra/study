/*
Before we get on with how modules and require() work, lets understand the following

1) Prototypal Inheriteance and function constructors
2) Pass by value and pass by reference
3) Immediately Invoked Function expressions (IIFE)
*/

// Function constructors.
// In javascript, a function can use the "this" keyword which automatically creates an empty object.
// By now you must be knowing that an object in javscript is nothing but a name and value pair. Think no more deeply than that
// Such functions which use "this" can tie properties and methods to the "this" object and the "this" object is automatically returned by Javascript
function Person(first, last) {
    this.firstname = first;
    this.lastname = last;
    console.log(this.firstname + " " + this.lastname);
}

var john = new Person('John','Doe'); //Note the use of new while creating an object from a function c'tor
var marc = new Person('Marc','Gimmy'); //Note the use of new while creating an object from a function c'tor

//What actually happens with the "new" keyword
/*
Javascript creates a new object called john. Every javascript object has a property called "__proto__" which tells
what is the objects prototype. By default it does not refer to anything. But with objects created using "new" syntax
the __proto__ refers to the function c'tors prototype method. This allows john object to access any methods and properties
on the functions prototype and is a standard way in Javascript to do inheritance
*/

// Now lets say you want to add another method/field to the john object. You do this using prototypal inheritance.
// A function in javascript is also an object, so it has methods and properties. Function c'tors have a property
// called prototype which can be used to add or extend all objects which are created using this function c'tor.
// Basically all objects have __proto__ property which points to the prototype property of the function c'tor.
Person.prototype.greet = function() {
    console.log('Greet function');
}

/* an object created from a Function ctor always has its implicit __proto__ property pointing to the prototype of the function c'tor */
/* So john.__proto__ points to Person.prototype and so does marc.__proto__ */
john.greet();
marc.greet();

console.log(john.__proto__ === marc.__proto__); // Note that === is always safe than == as it does not involve coercing.
console.log(john.__proto__ === Person.prototype);


// In javascript, primitives (Number, boolean, strings are always passed by value and Objects are always passed by reference


// IIFE - Very simple see below. A function that can be invoked immediately. To make a function a function expression
// wrap it inside round brackets and then you may invoke it. The big side effect is this whatever is written inside the function body
/* remain inside the function body only.  This is because everything is inside the function scope and is not valid outside.*/

var myVar = 2;

(function () {
    var myVar = 10;
    console.log(myVar);
} ());

console.log(myVar);

// nodejs/javascript uses IIFE heavily to implement module and require.

