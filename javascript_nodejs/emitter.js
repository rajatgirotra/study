/*
Events and Event emitter
In node there can be two types of events.

System events - Like file opened, socket open, memory full etc.
There is the libuv library we'll see later that takes care of the system events.

And there are custom events - Ie you can create your own events and attach listeners
to it.

Here well see the second type custom events. We'll come to system events by libuv later.
Node has its own event emitter module that allows you to create events and listeners
but here we'll create a small event emitter of our own just so you get an idea.
*/

//Create a function c'tor to create an Event Emitter.
function Emitter() {
    //empty object for now. Will hold
    //multiple property and values, where property will be the event
    //name and the value will be an array of listeners
    this.events = {}; 
}


//Lets extend the object created by the Emitter function c'tor
//by adding a function which takes an event type and listener and adds it to
//the event object
Emitter.prototype.on = function (type, listener) {
    //Check if we already have an array of listeners for this event
    //or is it a new one
    this.events[type] = this.events[type] || [];
    this.events[type].push(listener);
}

//Now a function to emit the event which will call all listeners
Emitter.prototype.emit = function(type) {
    //Array as a forEach property to iterate over it
    this.events[type].forEach(function (item) {
        //item will be the listener
        //javascript will call this function for each listener in the list
        item();
    });
}

//export the function c'tor
module.exports = Emitter;
