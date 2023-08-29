// import express as an ES6 module
import express from 'express';
import { fileURLToPath } from 'url';
import { dirname, sep } from 'path';
import compression from 'compression';

const app = express();

// disable express from setting an HTTP Response header "X-Powered-By: Express" in all its responses.
// it saves a few bytes + also doesn't tell malicious hackers too much about your technology stack.
app.disable('x-powered-by');


// the current javascript file/module name can be fetched as a URL using import.meta.url
console.log("this module file URL: " + import.meta.url);
// to convert this to a file path we do
const __dirname = dirname(fileURLToPath(import.meta.url)) + sep;
console.log("this module file fully qualified path: " + fileURLToPath(import.meta.url));

const cfg = {
    port: (process.env.PORT || 8110),
    dir : {
        root: __dirname,
        static: __dirname + 'static' + sep,
        views: __dirname + 'views' + sep
    }
};

console.dir(cfg, { depth: null, color: true });

// use EJS templates
// This sets EJS as the Express view engine with files contained in the views directory.
app.set('view engine', 'ejs');
app.set('views', cfg.dir.views);

// app.set('case sensitive routing', true) # normally no one does that

// The paths /hello/ and /hello match the same route unless you add
// app.set('strict routing', true)

// read about middleware functions in express below.
app.use((req, res, next) => {
    console.log(`a new http request received with url: ${req.url}`);
    next(); // never forget this or the request will hang
});

// another middleware that compresses responses sent to client. this will improve performance
app.use(compression());

// create a route (HTTP GET method).
// Routing determines which functions Express executes when it receives a request for a specific URL
/*
A routing function is passed these two objects:
An Express HTTP Request object ( req ), which contains details about the browser’s request.
An Express HTTP Response object ( res ), which provides methods used to return a response to the browser. We send “Hello, World!” text.
 */
app.get('/', (req, res) => {
   // res.send('Hello World!');
    res.render('message', {title: 'Hello World!'});
});

// app.put() -> for put method
// app.post()
// app.delete()
// app.all() --> for all http methods
// req.method gives you the request method inside the function


//create another route
app.get('/hello/', (req, res) => {
    // res.send('Hello again');
    res.render('message', {title: 'Hello again!'});
});

// app.use((req, res, next) => {
//     console.log(`a new http request received with url: ${req.url}`);
//     next(); // never forget this or the request will hang
// });

// express.static returns an Express middleware function. What are middleware functions. Express allows you to specify some actions to be taken
// along the way when a new request comes in. Example:
// Log each request in the log file or run some code on every request
// manipulate or change the request and response objects
// terminate a response — perhaps if the user isn’t logged in
// call the next middleware function
// each middleware function is given the req and res objects and the next object i.e. the next middleware function to execute.
// these middleware functions are executed in the sequence defined in code.
app.use(express.static(cfg.dir.static));

// this won't execute at all because the request is already handled by the app.get() function and a response is returned.
// so the code will never get here. So we need to move it at the top.
// app.use((req, res, next) => {
//     console.log(`a new http request received with url: ${req.url}`);
//     next(); // never forget this or the request will hang
// });

// should always be the last middleware to handle 404 errors
app.use((req, res) => {
    res.status(404).send('Page not found');
});


app.listen(cfg.port, () => {
    console.log(`server listening on port ${cfg.port}`);
});

// to allow other modules to use the cfg and app objects, we need to export it explicitly
export  { cfg, app };

/*
route expressions can be regular expressions also.
? --> denotes that the preceding character is optional. A route of /ab?cd/ matches the URL paths /abcd/ and /acd/
+ --> denotes that the preceding character must appear one or more times. A route of /ab+cd/ matches the URL paths /abcd/ , /abbcd/ , /abbbbbcd/ and so on
* --> denotes any number of characters. A route of /ab*cd/ matches the URL paths /abcd/ , /ab123cd/ , /ab-node.js-cd/ and so on.
A more complex route of /.+Script$/ matches the URL paths /JavaScript/ and /ECMAScipt/, but not /Scripting/. '.+' means one or more occurrences of any character

There is also an open source http://forbeslindesay.github.io/express-route-tester/ tool available to test express route paths.

You can also extract variable values from route expressions. The extracted values are available on the req.params object. You use a colon ":" to extract
variables from a route expression. eg: the route /user/:id matches any URL path starting /user/ that has a single segment—such as /user/123 or
/user/abc

// return a value for a user
app.get('/author/:name/book/:bookName', (req, res, next) => {
  console.log(`author: ${ req.params.name }`);
  console.log(` book: ${ req.params.bookName }`);
  next();
});

But slowly adding so many routes to your index.js will become unmanageable. So we should use the Router() object in express.
Express provides a router object to handle specific routes in separate js files so it remain manageable.
Let's see how it used in express_6.
*/