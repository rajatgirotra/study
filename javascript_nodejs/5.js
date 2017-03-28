/* The way javascript implements the require() and module is.
1) Nodejs wraps all of your code inside an IIFE automatically 
2) This way everything in your code becomes a module & remains within your module and doesnt effect
   anyone outside */

//so
function hello() {
    console.log('Hello World');
}

module.exports = hello;

//will be wrapped by nodejs as
/*
(function (exports, require, module, __filename, __dirname) {
    function hello() {
        console.log('Hello World');
    }

    module.exports = hello; 
})
*/

/* so every javascript file in nodesjs has the above 5 variables

1) exports which just points to module.exports
2) require - a require object
3) module - a module object representing this module.
4) __filename - name of this source file.
5) __dirname - directory path where this javascript file is.

/* If you download the nodejs source and step thru it, you'll see that nodejs creates a Module object and then calls all the
code inside it, and then returns the module.exports object, which is what require gets as output.
*/

