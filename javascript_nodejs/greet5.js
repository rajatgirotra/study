
module.exports = function Greetr() {
    this.greeting = 'Hello World.!!';
    this.greet = function() {
        console.log (this.greeting);
    }
}

