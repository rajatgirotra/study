/**
 * putting a ! suffix after getElementById tells Typescript that this function will never return null.
 * means that num1 id is definitely defined in the index.html.
 *
 * Also "as HTMLInputElement" is used to tell the type
 * of the element so that we can use .value on it. Not all elements have a .value member so telling it here explicitly
 * allows us to safely use .value on it.
 *
 * Also putting + befor num1.value means coverting the field from string to number. ".value" always returns string.
 */
var num1 = document.getElementById("num1");
console.log(+num1 + 50); // will be mathemetical add now. not string concatenation.
