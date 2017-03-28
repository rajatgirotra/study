var searchPeople = function(firstname, lastname, age, occupation, height) {
    return 'Jane Doe'
}

console.log(searchPeople) // This prints the actual code as the developer wrote it. or you can also say searchPeople.toString()

// So what AngularJS does, is that it parses the complete definition of the function we specify in the controller, and looks for special arguments
// preeceded by a dollar $ sign and sees which of those variables are defined inside AngularJS. for all those variables, it created a new instance
// and hands over to the function.

/*
AngularJS has a number of services defined (or call ir module). You can get access to them out of the box in your controller, just be specifying the
correct variable name in argument list. Now return back and see how we use the $scope, $log, $filter etc angular objects.

Create an html and include angular and then this script and then uncomment the below line
console.log(angular.injector().annotate(searchPeople));
*/
