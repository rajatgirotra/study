// Please read README_4.txt
/* Each groovy class is compiled to Java bytecode - so there is a 1 to 1 mapping between each groovy class and Java class. */
/* Lets explore the list and map interface of groovy here alon with some other features.*/

/* Remember that every variable in groovy is an object. */

println "Hello, world"

for(arg in this.args) {
	println "Argument: " + arg
}

//List interface.
def list = [ 1, 2, 'Hello', new java.util.Date() ]
assert list.size() == 4
println "List size: " + list.size()
assert list.get(2) == "Hello"
assert list[2] == "Hello"
println "Date: " + list[3]

//Iterating over a list
for(i in list) {
	println i
}

//Declaring a map
def simpleMap = ['Name':'John', 'Location':'North Calorina', "Pete":100, "Rick":-987.234];
assert simpleMap.size() == 4
println simpleMap['Name']
println simpleMap.get('Location')
println simpleMap.Pete //So now you have 3 ways for printing out values in a map. First by index, then by get() function and then by the key name.

//Creating an empty list and map and printing their size.
emptyList = []
emptyMap = [:]

println "Empty List Size: " + emptyList.size()
println "Empty Map Size: " + emptyMap.size()

/*
Please read 5.groovy
*/
