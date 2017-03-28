/*
Here we'll see what happens when we use multiple controllers.
See 14.html where we have two controllers having scope variables with the same name.
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", "$http", function($scope, $timeout, $filter, $log, $http) {

    $scope.name = 'Main';

}]);


// Second controller
myAngularApp.controller('SecondController', ["$scope", "$timeout", "$filter", "$log", "$http", function($scope, $timeout, $filter, $log, $http) {

    $scope.name = 'Second';

}]);

/* You can have same name for variables in the scope object because Angular gives each controller a separate copy the the scope and other service objects.
   So one controller is independent of the other
*/
