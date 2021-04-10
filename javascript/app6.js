/* lets create an object and add properties and methods on it. */

var person = new Object();  // not the best way to create objects but good to know.

person["firstname"] = "Rajat";
person["lastname"]  = "Girotra";

var firstpropertyname = 'firstname';

console.log('Person', person);
console.log('Person first name: ' + person[firstpropertyname]);
console.log('Person.lastname: ' + person.lastname);

person.address = new Object();
person.address.street = 'Simei Street 4';
person.address.city = 'Singapore';
person.address.state = 'Singapore';
console.log('Person.address: ', person.address);


// creating objects using object literals.
var someone = {
      firstname: 'Rajat', lastname: 'Girotra',
      address: {city: 'Singapore', state: 'Singapore', street: 'Simei Street 4' }
};
console.log('Someone', someone);

function greet(arg) {
    console.log('Hi ' + arg.firstname);
}

greet(person);
greet(someone);
greet({firstname: 'vidhu'}); // creating object on the fly and passing to a function
