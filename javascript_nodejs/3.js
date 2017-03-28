// In javascript functions are first class. 
/*
This means that you can pass functions around just like you can in C++
*/

function greet() {
    console.log('Hello Rajat');
}

function logGreeting(fn) {
    fn();
}

// You can also define functions like this
var myName = function() {
    console.log('My name is Anthony on Service');
}


logGreeting(greet); //passing function greet.
myName();

// Infact you can pass the definition of a function as an argument on the fly. Just like
// anonymous class in Java or a lambda function in C++
logGreeting(function() {
    console.log('Logging Greeting');
});
