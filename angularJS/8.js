/*
Here we'll use the ng-model directive. which is the most important directive (custom attribute) of
AngularJS. It provides a two way data-binding between the modal and the view.
If anyone asks what is AngularJS, say it provides a two way data binding between the Javascript DOM
and the view.
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", function($scope, $timeout, $filter) {

    // Note that as you change the view (text in the box), the modal updates (the handle variable)
    $scope.handle = '';

    // Next lets use the filter service to always show the handle in lower case
    $scope.lowercasehandle = function() {
        return $filter('lowercase')($scope.handle);
    }
}]);
