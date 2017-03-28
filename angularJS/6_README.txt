Ok you already know what a minified version of javascript is.
It is just a version of javascript with all white space and comments removed.
So as to reduce the download size. Also a javascript minimizer will replace long variable names
with short ones. This can actually cause a problem.

For example:

myApp.controller('MyController', function($scope, $log) {
});

will be reduced to

myApp.controller("MyController",function(o,l){});

This is a problem for Angular as it cannot do dependency injection as the function arguments are not $scope and $log anymore.
So Angular guys came out with a workaround syntax.

myApp.controller('MyController', ["$scope", "$log", function($scope, $log) {
}]);

This is an alternate and preferred syntax. Here the minified version is:

myApp.controller("MyController",["$scope","$log",function(o,l){}]);

The minifier can never alter values inside an array, so $scope and $log are not modified inside an array.
AngularJS will now copy $scope to argument o and $log to argument l.

So from now on, use this syntax instead.
