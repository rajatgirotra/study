console.log($("h1").attr("reply"))

/*
Hit F12 in Chrome to bring up google developer tools and view console which says "HelloBack!"

Ok, so HTML says that if you want to describe some custom attributes, define them as data-<attributeName>, eg: data-reply
Then it will consider it as official HTML 5 way of defining custom attributes.

Also AngularJS uses ng-<attributeName> to define a number of attributes and makes decisions based on those attributes
If you really want to be HTML 5 compliant, it also allows data-ng-<attributeName> which has the same behavior as ng-<attributeName>

*/
