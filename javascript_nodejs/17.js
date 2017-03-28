/* Javascript has introuced a new standard called ECMAScript 2015 or ES.
   This introduces classes which is just syntactic sugar over ptrototypal inheritance.
   So function c;tor can be written as
*/

'use strict';

class Person {
    constructor(fname, lname) {
        this.firstname = fname;
        this.lastname = lname;
    }

    // Declaring a function inside a class is  same as creating a function on the prototype
    greet() {
        return `${this.firstname} ${this.lastname}`
    }
}


class Policeman extends Person {
    constructor(fname, lname) {
        super(fname, lname);  //short cut for base class function c'tor.
        this.batchnumber = 1234;
    }

    details() {
        return 'Policeman: ' + this.greet() + '   BatchNumber: ' + this.batchnumber;
    }
}


var police = new Policeman('Atul', 'Rustogi');
console.log(police.details());  // Will show undefined for Person firstname and lastname unless line A is uncommented.
