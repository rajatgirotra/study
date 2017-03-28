//Please read 4.groovy first
//We'll study closures here
/*
A closure is an object which has a single method which is invokable with an arbitrary number of parameters
*/

def closure = {param -> println ("Hello  ${param}")}
closure.call("World!!");

closure = { greeting, name -> println ("${greeting} ${name}")}
closure.call("Cruel"," World");
//closure.call("Goodbye", "Cruel"," World"); //Only two parameters allowed

closure = {println ("Hello ${it}")} //If no argument is specified, then the default argument "it" is always available.
//closure = {println "Hello " +  it} //If no argument is specified, then the default argument "it" is always available.
closure.call("Mike");
//closure.call("Mike", "Jim"); //Only one parameter allowed.

[1, 2, 3].each() {key -> print "${key}-"} //each is a special closure (java.util.ArrayList.each()) which is defined inline and that function
				//is executed for every item in the list.
			//Similarly we have an each() method for map also.

//[1, 2, 3].xyz() {key -> print "${key}-"}  //this gives an error that java.util.ArrayList.xyz() is not available.

println ""
["k1":"v1", "k2":"v2"].each() { key, value -> println ("${key} = ${value}") }

//Different ways of defining/calling a closure

[-1, -2, -3].each() { key -> print "${key} " }
println ""

[-1, -2, -3].each { key -> print "${key} " } //omitted the round brackets in each() and surround by zero pair of round brackets.
println ""

[-1, -2, -3].each ({ key -> print "${key} " }) //omitted the round brackets in each() and surround by one pair of round brackets.
println ""

[-1, -2, -3].each (({ key -> print "${key} " })) //omitted the round brackets in each() and surround by two pair of round brackets.
println ""

/*When you define some function whose last parameter is a closure, you can write the definition of the closure outside the definition
of the function Eg: */
def someFuncFoo(int i, Closure c) {
	c.call(i);
}

//Calling the function someFuncFoo
[789, 234, -765].each { someFuncFoo(it, {item -> print "${item}  "})}

//A look at a lot of other methods of collections and strings

//Collect : collect the return value of calling a closure on each item in a collection
println ""
def values = [1, 2, 3].collect { it * 3 }
assert values == [3,6,9]
println values

//find : Finds the first items matching the closure predicate.
def item = [1, 2, 3].find { it > 2 }
assert item == 3
println "Item: " + item

//findAll : Finds all the items matching the closure predicate.
item = [1, 2, 3].findAll { it >= 2 }
assert item == [2,3]
println "Item: " + item

//inject: allows you to pass a value into the first iteration and the resultant is passed to the second iteration and so on.
//See below how it can be used.
def cnt = [1,2,3].inject("counting: " ) { str, number -> str + number }
println cnt

def sum = [1,2,3].inject(0) { start, increment -> start + increment }
println "sum: " + sum

//every: returns true if every item satisfies the predicate.
def boolValue = [1,2,3].every { it > 1 }
println "1,2,3 are all greater than 1: " + boolValue

//any: returns true if any item satisfies the predicate.
boolValue = [1,2,3].any { it > 2 }
println "is any of 1,2,3 greater than 2: " + boolValue

//max, min and join - all these are self explanatory
def max = [1,2,3].max()
println "Max: " + max

def min = [0,1,2].min()
println "Min: " + min

def joiner = [1,2,3].join("-")
println "Join of 1,2,3: " + joiner

/*
Please read 6.groovy next
*/
