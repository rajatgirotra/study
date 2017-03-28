/*
Exactly like 12.js except one thing. When u use util.inherits() the methods and properties on the EventEmitter prototype
are accessible by the Greetr() object; but what about any methods and properties defined within the EventEmitter function c'tor
itself?? Those are not inherited by Greetr yet. So what you have is partial inheritance. The way to fix this is line marked as A.
*/
var EventEmitter = require('events');
var util = require('util');

function Greetr() {
    EventEmitter.call(this);   /// ----->>> A. We explicitly call the EventEmitter function ctor with the this parameter as the object we are creating
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

