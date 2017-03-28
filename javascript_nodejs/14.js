// .call and .apply methods on functions

//simple function c'tor
function Greetr() {
    this.firstname = 'Jane';
    this.lastname = 'Doe';
    this.greet = function () {
        console.log('Hello ' + this.firstname + ' ' + this.lastname);
    }
}

var greeting = new Greetr();
greeting.greet(); // By default, the greet function will act on the this object

// But sometimes, you can just borrow the function inside the function c'tor (greet here) and make it act on
// another object which is not this. may some object created on the fly or any other object
var person = {
    firstname: 'Rajat',
    lastname: 'Girotra'
}

greeting.greet.call(); // by default, calling call() with no parameter will make firstname and lastname as undefined.
greeting.greet.call( {firstname: 'Rajat' } ); // will print "Hello Rajat undefined"
greeting.greet.call(person); //will print "Hello Rajat Girotra"

// .apply also behaves in the same way
greeting.greet.apply();
greeting.greet.apply( {firstname: 'Rajat' } );
greeting.greet.apply(person);

// difference - .call and .apply behave differently when we pass parameters to function.
// in .call we pass parameters individually and in .apply we pass parameters as an array.

var policeman = {
    name: 'Nick Welsh',
    batch: 2009,
    details : function(category, division) {
        console.log(`Category ${category}, Division ${division}, Name ${this.name}, Batch ${this.batch}`); // using backticks with ${} syntax is EcmaScript 6 (ES6) standard.
    }
}

policeman.details('SHO', 'Inspector');
policeman.details.call({name: 'Some Name'}, 'DCP', 'Hawaldar');
policeman.details.apply({name: 'Some Name', batch : 2015}, ['IG', 'Highest']);
