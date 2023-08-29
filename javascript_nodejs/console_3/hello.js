//nodejs provides a standard process module which has important properties like
// env --> to read environment variables
// argv --> to process command line arguments.
// argv[0] == node
// argv[1] == name of the startup javascript
// argv[2] onwards.. == command line arguments

// A simple function to print "Hello " followed by name provides as argument/ or name provides in the $USER env variable / or "world"
// also capitalize the first character of every word and everything else should be lowercase

const nameArg = capitalize(process.argv[2] || process.env.USER || process.env.USERNAME || 'World');

function capitalize(str) {
  return str.trim().split(' ').map(word => word.charAt(0).toUpperCase() + word.slice(1).toLowerCase()).join(' ');
}

console.log(`Hello ${nameArg}`);
