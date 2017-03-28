/*
The first thing we need to do with angularJS is to create an angular module Object
*/

//the name of the module is 'myApp', and the second argument is a list of dependencies on other angular modules.
//see https://code.angularjs.org/1.5.0-beta.2/ and you'll see other modules like angular-resource.js, angular-messages.js
//When your angular app uses any of the functions/services of these modules, you must list them here. Example, we'll use ngMessages module
//which provides form validations
var myAngularApp = angular.module('myApp', ['ngMessages', 'ngResource']);

//Next we need to tell our angular app what part of the view (HTML) will this app control. This is done using the data-ng-app attribute.
//See html element in the corresponding view.

//From now on everything else will be added to the myAngularApp variable.

//Next we need to declare a controller
myAngularApp.controller('MainController', function($scope, $log, $resource) {
    //All code associated with the controller goes here.
    //Next we need to go back to the view and tell which part of the view (which sub-part is this controller controlling)
    //We do this using the data-ng-controller attribute

    //Before going further, please read function_strings.js and then return here
    console.log($scope);    
    $log.info("This is an info message");
    $log.warn("This is a warning");
    $log.error("This is an error");

    //For a complete list of services, google AngularJS services or AngularJS modules.

    // 1) We have put a dependecny on ngMessages which provides form validations. See the HTML form element.

    // 2) Next there is another service called ngResource which provides a convinent way of grabbing resources from the web
    // using http
    

    //You can even add properties on the $scope object
    $scope.firstname = 'Rajat';
    
    console.log($scope);

    //In the next section we'll see javascript minimizer and after that we move to working with real javascript code.
});
