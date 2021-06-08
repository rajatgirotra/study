About typescript.

Typescript is just a superset of javascript. It allows you to write better javascript code.
Typescript introduces types and many other features that you can use to write good javascript code like generics etc.
Eventually all the typescript code has to be converted to javascript. This is required as the browser doesnt understand typescript. it only understand javascript. This conversion is done by typescript compiler "tsc". 

You can install "tsc" using npm (nodejs package manager).
"npm install -g typescript"


to play with typescript, create an empty project folder. create an index.html which runs an external "app.js" javascript file.
then play and write all your typescript code in ""app.ts" and compile it using "tsc". tsc will output "app.js" which index.html will run in the browser.

however running tsc each time and reloading browser can be a bit tedious. to automate it, run "npm init" in the project folder. This will create a package.json file. Then run "npm install --save-dev lite-server". then add "lite-server" as the main starting point in package.json
 "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "start": "lite-server"
  },

lite-server is a development http server which always serves index.html file next to package.json and also reloads the page everytime you modify any file in that project folder. So we just compile app.ts to app.js and lite-server will reload the output in the browser. lite-server will serve at localhost:3000/

then start the server by typing "npm start"

-----------------------------------------------------------------------------------------------------------------------------------------------

We also have an ngc compiler called "Angular compiler"

tsc and ngc have different purposes and it's not about selecting one over the other.

tsc is a TypeScript compiler, and you need it to generate JavaScript if your app is written in TypeScript.

ngc is an Angular-specific compiler. It doesn't turn the TypeScript code into JavaScript. It does a "finishing touch" to make your app bundles ready for rendering by the browser. In particular, it turns your components templates into inline JavaScript. If you do a prod build with Ahead of Time (AoT) compilation, the ngc does its part before the bundles are built. In dev mode we use Just-in-Time compilation: the templates are not precompiled, the ngc compiler is included into the bundles, and it compiles the templates after the browser loaded your bundles.
-----------------------------------------------------------------------------------------------------------------------------------------------
