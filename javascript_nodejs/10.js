
//read emitter.js first and then return here
//Get the Emitter object
var Emitter = require('./emitter')
//var Emitter = require('events')

var myevents = require('./event').myevents

emitter = new Emitter();

//Create a listener
var greeting_listener_1 = function () {
    console.log('greeting_listener_1 called. greeting event occurred');
}

//emitter.on('Greeting', greeting_listener_1);
emitter.on(myevents.GREET, greeting_listener_1);

//Add another listener on the fly
//emitter.on('Greeting', function() {
emitter.on(myevents.GREET, function() {    
    console.log('Hello World Greeting');
});

// Now just emit the event
//emitter.emit('Greeting');
emitter.emit(myevents.GREET);

console.log('After listeners');

// One bad thing here is that the event name is being repeated. which can be error prone
// A better way is to store event names at a common place like a module.
// Lets define event.js

// Now to use the node event emitter, you need to require the 'event' module.
// So just changing one require line at the top should do the trick for you.
