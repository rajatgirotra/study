/*
Many times you want to send some information in the URL, like some parameters in a query string, like a google search has parameters in the URL itself
in a get request. To support this in a Single Page App with Angular, you suffix your templateUrl with a colon followed by some identier.
This identifier automatically gets the query string specified after the URL and is also available automatically in the $routeParams as you can see below.

So by now you have seen $location.path(), $routeProvider, and $routeParams
*/

var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource', 'ngRoute']);

/* First read the controller code then come here */
myAngularApp.config(function($routeProvider) {

    $routeProvider

        .when('/', {
            templateUrl: 'pages/third.html/:qs',
            controller: 'MainController'
        })
});

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", "$http", "$location", "$routeParams", function($scope, $timeout, $filter, $log, $http, $location, $routeParams) {

    $scope.name = 'Third Page';
    $scope.qs = $routeParams.qs;

}]);
