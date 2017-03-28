/* Let see another example of .call to make it more clear */

var util = require('util');

function Person () {
    this.firstname = 'Jane';
    this.lastname = 'Doe';
}

Person.prototype.greet = function() {
    return `${this.firstname} ${this.lastname}`
}

function Policeman() {
    //Person.call(this);  // --->>> A
    this.batchnumber = 1234;
}


util.inherits(Policeman, Person);  // implies Policeman.prototype = Person
Policeman.prototype.details = function() {
    return 'Policeman: ' + this.greet() + '   BatchNumber: ' + this.batchnumber;
}

var police = new Policeman();
console.log(police.details());  // Will show undefined for Person firstname and lastname unless line A is uncommented.
