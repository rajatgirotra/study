/*
*/
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

myAngularApp.controller('MainController', ["$scope", "$timeout", "$filter", "$log", function($scope, $timeout, $filter, $log) {

    // Note that as you change the view (text in the box), the modal updates (the handle variable)
    $scope.handle = '';

    //Let manually add a variable to the watch list and see when it is updated.
    $scope.$watch('handle', function(newvalue, oldvalue) {
        $log.info('OldValue ' + oldvalue + '   NewValue ' + newvalue);
    });

    // The caveat is that if I use a pure javascript function which runs asynchronously and we change the scope inside this function, then
    // angular will never know that the scope changed. In these odd cases, we have to explicitly tell AngularJS to run the digest loop.
    //eg: setTimeout() function which runs a function asynchronously after the specified number of milliseconds.
    // setTimeout(function() {
    //     $scope.handle = 'newTwitterHandle'; //function changed inside a javascript function
    //     $log.log('scope changed');
    //     $log.info($scope);
    // }, 3000);

    // To fix this issue we need to tell angular explicitly to run the digest loop via the apply method
    setTimeout(function() {
        $scope.$apply(function() {
            $scope.handle = 'newTwitterHandle';
            $log.info('scope changed');
        });
    }, 3000);
}]);
