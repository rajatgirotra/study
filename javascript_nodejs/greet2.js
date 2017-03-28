var greet = function() {
    console.log('Greetings 2!!');
}

module.exports.greet = greet;

/*
Or better, use
module.exports.greet = function() {
    console.log('Greetings 2!!');
}
*/

