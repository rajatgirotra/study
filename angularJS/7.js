/*
Here we'll see scope service and how it is used.
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", function($scope, $timeout) {
    //the scope object is the glue between the modal and the view.
    /* You can add properties to $scope object which are available in the view by
       enclosing them in {{ }} (called moustaches)
    */
    $scope.name = 'Rajat'; // see the <h1> tag in 7.html

    // Now lets use the timeout service which provides a timer and a function to
    // run when the timer expires
    //Change the name property after three seconds
    $timeout(function() {
        $scope.name = 'Mike';
    }, 3000);
}]);
