Debugging nodejs. There many ways to debug. 
1) first is to write good code, so there are not many bugs

2) use a linter like eslint

3) NODE_ENV environment variable. A common way is to export NODE_ENV variable to dev or production. Then based on the setting, you can decide in code
whether to log or not
export NODE_DEV=development
//app.js
const DEVMODE = (process.env.NODE_ENV !== 'production');

if(DEVMODE) {
console.log('application started in development mode';
}

4) Node.js provides a util module which has a debuglog function. This function takes a logger name and returns a function which can be called with the log message. Example:
const util = require('util');
const myapplog = util.debuglog('myapp');
myapplog('This is a log message from myapp');
We can now turn on/off the myapp logging using env variable NODE_DEBUG. If NODE_DEBUG=myapp, the messages will be logged.
NODE_DEBUG can also be given regular expression, so it can match multiple registered logger names.

5) console.log() and all of its different variants.
https://nodejs.org/api/console.html

6) enable helpful command line options that can reveal possible issues. Example:
node --trace-warnings
node --throw-deprecation
node --enable-source-maps

7) Use a logging API like winston, and many others

8) Use the node.js inspect debugger.
node inspect <app.js> (in GDB terminology, app.js is the inferior under the debugger). You can put breakpoints and single step through the code.
node v8 engine has its own inspector and debugging client. start it like shown below. It breaks at the first line of code for you app.

9) debug using browser developer tools. example:
node --inspect server_4/webhello.js ## or nodemon --inspect server_4/webhello.js
Then just head to brave://inspect/#devices and click "Inspect"

10) Other options like IDE tools in Visual Studio code, Jetbrains also provide their own debugging capabilities.
Also look at ndb which provides good debugging experience.

See express_5 folder next.