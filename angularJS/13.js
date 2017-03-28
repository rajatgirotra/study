/*
$http service
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", "$http", function($scope, $timeout, $filter, $log, $http) {

    $log.debug('Doing something');
    $http.get('http://sg1e-sudat01/research/2015-11-19/ose/day/transactions.json')
        .success(function(result) { //result will the json we get back.
            $scope.result = result;
            $log.info('HTTP Request succeeded');
        })
        .error(function(data, status) { // any status and data we might get
            $log.error('HTTP request failed with data ' + data + ' and status ' + status);
        });
      /* For now our request will fail with error:
         No 'Access-Control-Allow-Origin' header is present on the requested resource. Origin 'null' is therefore not allowed access.
         Actually we are doing an XMLHttpRequest to a different domain than our page is on. So the browser is blocking it as it usually allows a request in the same origin for security reasons.
         You need to do something different when you want to do a cross-domain request. Google for Cross Domain XmlHTTPRequest in your free time.
      */

      //Similarly we can also do a post instead of get. See the online documentation for more details.

}]);
