// Object.create()

/*
We've already seen one way of inheritance using function c'tors and prototypal inheritance.
There is another way to achieve the same.
*/

// Define a simple person object with firstname, lastname and greet function
var person = {
    firstname :  '',
    lastname : '',
    greet: function () {
        return this.firstname + ' ' + this.lastname;
    }
}


// You can now use the Object.create(superObject) syntax
var john = Object.create(person);
// The above syntax will create an empty object and
// set john.__proto__ to be on the fly object created from person.
// Note that since person is not a function c'tor; it does not have any
// prototype property. So this is slighylt different. Here the prototype
// is created on the fly and has exactly the same properties and methods as person
console.log(john.__proto__);
console.log(person.prototype);   // should be undefined.
console.log(john.__proto__ === person.prototype);   // should be false
console.log('Hello ' + john.greet());  //first name and lastname should be empty
// set first name and lastname now
john.firstname = 'John';
john.lastname = 'Doe';
console.log('Hello ' + john.greet());

var jane = Object.create(person);
jane.firstname = 'Jane';
jane.lastname = 'Doe';
console.log('Hello ' + jane.greet());

