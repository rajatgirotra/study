// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Operator_Precedence
var a = 3 + 4 * 5;
console.log(a); // 23

var x = 2, y = 3, z = 4;
x = y = z;
console.log(x); // 4
console.log(y); // 4
console.log(z); // 4

// coercion - converting a value from one type to another.
a = "hello " + ' world'
console.log(a); // "hello world"

a = 1 + '2' // js coerces number to string
console.log(a);  // 12

// comparison operators
console.log(1 < 2 < 3);  // true
console.log(3 < 2 < 1); // why true. because of operator associativity 3 < 2 is done first so it becomes false < 1 and js will coerce false to number 0 so it becomes 0 < 1 i.e true.

// to find what Number something coerces to in js use Number class.
// Number(false) = 0, Number('hello') etc in developer tools
// Number(true) = 1, 
// Number('hello')  = NaN
// Number(null) = 0
// Number(undefined) = NaN

// coercion can cause some confusion when you do equality comparisons. because if the types on both sides are not equal, one is coerced to the other. example:
console.log('3 == 3: ',  3 == 3);
console.log('"3" == 3: ', "3" == 3); // "3" is coerced to 3
console.log('false == 0: ',  false == 0); // false is coerced to 0
console.log('null == 0: ',  null == 0); // null doesnt coerce here, although Number(null) returns 0
console.log('null < 1: ',  null < 1); // now null coerces. 
console.log('"" == 0: ',  ""==0 );
console.log('"" == false: ',  ""==false );
// so this is very unpredictable and we should not rely on this. prefer using strict equality, i.e === or !==
// strict inequality doesnt coerce and if the two types arent equal, it returns false. So it is a life saver.
//
console.log('3 === 3: ',  3 === 3);
console.log('"3" === 3: ', "3" === 3); // "3" is coerced to 3
console.log('false === 0: ',  false === 0); // false is coerced to 0
console.log('null === 0: ',  null === 0); // null doesnt coerce here, although Number(null) returns 0
console.log('null < 1: ',  null < 1); // now null coerces. 
console.log('"" === 0: ',  ""===0 );
console.log('"" === false: ',  ""===false );

// Rule of Thumb: use === in js almost always. use == only if you know what you are doing

// just like Number, you also have Boolean() to see what different values coerce to in boolean. example:
//Boolean(undefined) = false
//Boolean(null) = false
//Boolean("") = false
