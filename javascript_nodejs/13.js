/*
Exactly like 12.js except  that we are passing parameters to our listeners
*/
var EventEmitter = require('events');
var util = require('util');

function Greetr() {
    this.greeting = 'Hello World! ';
}

util.inherits(Greetr, EventEmitter); // implies Greetr.prototype = EventEmitter.prototype

// Create a greet method on the Greetr prototype which will log the greeting
// REMEMBER: use Greetr.prototype obly after using util.inherits as that function overrwrites
// Greetr.prototype anyway
Greetr.prototype.greet = function(data) {
    console.log(this.greeting + ': ' + data);
    this.emit('greet', data);
}

var greeter1 = new Greetr();
greeter1.on('greet', function (data) {
    console.log('someone greeted : ' + data);
});

greeter1.greet('Rajat');

