/*
Single Page Webapplications are those where there is only one http request to get all page details and data. And then that page contains hashes to move from
one location (link) to another. So you dont need to do multiple GET requests and wait for browser to load your page. More or less like a desktop application.

Now Angular provides a service called the location service built-in within angular main javascript file which provides the current hash path.
Also it provides a router provider service as a separate library which is used to configure hash specific implementation of your own. Lets see how.
*/

var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource', 'ngRoute']);

/* First read the controller code then come here */
myAngularApp.config(function($routeProvider) {

    $routeProvider

        .when('/', {
            templateUrl: 'pages/main.html',  //the physical location of an html page
            controller: 'MainController'
        })

        .when('/second', {
            templateUrl: 'pages/second.html',  //the physical location of an html page
            controller: 'SecondController'
        })
        
        //Now that you already provide the controller information in the route provider, we dont need ng-controller again in the html
        //What we need now is an ng-view directive.
});

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", "$http", "$location", function($scope, $timeout, $filter, $log, $http, $location) {

    $scope.name = 'Second';

    // the first thing is that $location.path() gives you the current hash. We can log it to the console and see for ourselves.
    $log.debug($location.path());

    // next it provides another service called $routeProvider to setup routing to different html's based on different hash locations.

}]);

myAngularApp.controller('SecondController', ["$scope", "$timeout", "$filter", "$log", "$http", "$location", function($scope, $timeout, $filter, $log, $http, $location) {

    $scope.name = 'Second';

}]);


// Add
