/*
Node has a util.js module which provides an "inherits" function which takes two parameters

util.inherits(baseCtor, superCtor) where superCtor must be a function c'tor and does
baseCtor.prototype = superCtor.prototype, so that base object will have access to all
properties and methods on the prototype of the superCtor. This is heavily used in nodejs
where almost all modules inherit from the EventEmitter module so they have access to "on"
and "emit" functions on the EventEmitter prototype. See below example */

var EventEmitter = require('events');
var util = require('util');

function Greetr() {
    this.greeting = 'Hello World! ';
}

util.inherits(Greetr, EventEmitter); // implies Greetr.prototype = EventEmitter.prototype

// Create a greet method on the Greetr prototype which will log the greeting
// REMEMBER: use Greetr.prototype obly after using util.inherits as that function overrwrites
// Greetr.prototype anyway
Greetr.prototype.greet = function() {
    console.log(this.greeting);
    this.emit('greet');
}

var greeter1 = new Greetr();
greeter1.on('greet', function () {
    console.log('someone greeted');
});

greeter1.greet();

