/*
Here we will see some more AngularJS directives
ng-if
ng-show
ng-hide
ng-click
ng-class
ng-cloak
ng-repeat  and others
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", function($scope, $timeout, $filter, $log) {

    // Define a scope variable
    $scope.characterCount = 8;

    $scope.onClick = function() {
        $log.debug('Some one clicked');
        alert('Someone clicked');
    };

    $scope.rules = [
        { rulename: 'Same rule no' },
        {  rulename: 'Some rule for script' } ];
}]);
