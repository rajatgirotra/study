// you already know that require() takes the path of the javascript file.
// If you dont specify the .js extension, it will assume it. But what if the js file is not found.??
// It will try to find a directory with that name and then look for index.js inside that.
// Lets see that.
// Also we'll see that Nodejs has a JSON to javascript convertor to convert JSON Objects to javascript, we'll see that also.

var lang = require('./language');
lang.english();
lang.spanish();
