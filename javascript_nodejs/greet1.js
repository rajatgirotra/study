var greet = function () {
    console.log ('Greeting 1');
}

module.exports = greet;

/*
Also you can avoid creating the greet variable by doiing
module.exports = function () {
    console.log ('Greeting 1');
}
*/

