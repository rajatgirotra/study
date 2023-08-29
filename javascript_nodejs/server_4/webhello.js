// create a minimal http server. It will always just return statuscode success (i.e 200 OK) and return <p>Hello ${URL}</p>
// make it run on port 8888 by default or take the port from command line or PORT env variable

const http = require('http')

const port = (process.argv[2] || process.env.PORT || 8888);

http.createServer((req, res) => {
  console.log(req.url);

  // abort favicon.ico requests.
  if (req.url.includes('favicon.ico')) {
    res.statusCode = 404;
    res.end('Not found');
    return;
  }

  const nameArg = capitalize(req.url.replace(/[^\w.,-]/g, ' ').replace(/\s+/g, ' ').trim() || 'World');
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/html');
  res.end(`<p>Hello ${nameArg}!</p>`);
}).listen(port);

console.log(`Http server listening on port ${port}!`);

function capitalize(str) {
  return str.trim().split(' ').map(word => word.charAt(0).toUpperCase() + word.slice(1).toLowerCase()).join(' ');
}


// you can run it using "node server_4/webhello.js" or
// npm install nodemon -g (nodemon is nodemonitor. It monitors javascript files for any changes and reloads the http server automatically).
