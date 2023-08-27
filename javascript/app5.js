/*

The keywords let and var both declare new variables in JavaScript. The difference between let and var is in the scope of the variables they create:

Variables declared by let are only available inside the block where they’re defined.
Variables declared by var are available throughout the function in which they’re declared.

*/
function varScoping() {
  var x = 1;

  if (true) {
    var x = 2; // can be declared again.
    console.log(x); // will print 2
  }

  console.log(x); // will print 2
}

function letScoping() {
  let x = 1;

  if (true) {
    let x = 2;
    console.log(x); // will print 2
  }

  console.log(x); // will print 1
}
// In varScoping(), one x variable is used throughout the function, even though an x variable is declared in two different places with different values.
// even if we replace the first "let x = 1" with "var x = 1", still we will say output as 2 and 1.


function nestedScopeTest() {
  if (true) {
    var functionVariable = 1;
    let blockVariable = 2;
     
    console.log(functionVariable);
    console.log(blockVariable);
  }

  console.log(functionVariable);
  console.log(blockVariable); // will throw an error.
}

varScoping();
letScoping();
nestedScopeTest();

// One final point to note is that when working outside of function bodies, at a global level, let does not create a property on the global object, whereas var does. Therefore:
// Global variables
var x = 1;
let y = 2;
console.log(this.x); // will print 1
console.log(this.y); // will print undefined
