/*
We'll see what are hashes and how to use them with Angular.
First go to 15.html and see what a fragment identifier is. After that lets just an event listener whenever the hash changes. Ie. whenever someone presses a link which jumps to a hash.
A hash change is said to have occurred.
*/

// Add hashchange event listener
window.addEventListener('hashchange', function() {
    console.log('Hash Changed! ' + window.location.hash); //window.location.hash gives you the current hash.
    /* Now if the anchor #bookmark does not exist, then the browser has nowhere to jump to. However, Javascript still fires the event, and gives the new value of hash. :) 
   This can be exploited. Try this
   file:///home/rgirotra/rajatgirotra_practice/trunk/angularJS/15.html#bookmark/1/1/2
   you can do like 
   if(window.location.hash === 1 then do 1)
   else if(window.location.hash === 2 then do 2) etc etc.

    Lets see how we can use hashes to implement Single Page Web Applications
    */
    

});


var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", "$http", function($scope, $timeout, $filter, $log, $http) {

    $scope.name = 'Main';

    $scope.range = _.range(50);
    console.log($scope.range);

}]);



// Add
