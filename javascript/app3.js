/* each execution context in javascript also has access to the outer/lexical environment
 * this means that if function a() and function b() are written at global scope, then inside these functions they
 * can access variables and function declared in the outer/lexical environment. i.e. the global execution context here.
 *
 * similarly if function x() is defined inside function y(), function x() can access variables in function y()
 */

function b() {
    console.log(myvar);
}

function a() {
    var myvar = 2;
}

var myvar = 1;
b();

/* above when b() is called myvar doesnt exist in its execution context, so javascript will look for myvar in its outer environment
 * which is the global execution context and find myvar=1 there.
 * if I move function b() inside function a(), then myvar will be 2
 */

