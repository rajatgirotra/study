function greet(name) {
    name = name || 'rajat'
    console.log(name); // undefined when greet() is called without parameter
    console.log('hello ' + name); // shows 'hello undefined'
}

greet(); // passed without parameter
greet('vidhu')

// before ES6, developers used a neat trick to set a default for name if name is undefined. the first line of the function would be:
// name = name || "default value"; || returns the first operand that coerces to true.
