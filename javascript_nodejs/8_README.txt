npm (Node package manager)

npm help
npm link --> Very important. It symlinks your locally working project as a global package so your fellow developers can use it. You dont need to keep installing it after every change to share with your colleagues.
npm install (install packages, locally or globally)
npm config (get/set and list configuration)
npm list (list packages)
npm search
npm init (to initialize a new node project)
npm help package.json (package.json as certain defined keys that you must read and understand)
npm install <package_name> --save-dev
npm outdated --global --> list global packages that are outdated.
npm update (will read package.json and update packages based on dependencies specified)
npm update <packageName> --> will only update that package
you can also maually edit package.json and then run "npm install" to update package dependencies.
npm uninstall

Also, some packages don't work if installed locally (example: eslint). In those cases you can use npx command.
npx --> a nodejs binary to run a command from a local or remote npm package (example npx cowsay "I love node.js!")
npx eslint file.js should work (basically node will just download the package once in the cache and run the command from there instead of globally or locally installing the package)

package versioning in package.json.

1.2.33 : install an exact version
>1.2.33 : install a version greater than 1.2.33 ( 2.0.0 is permitted)
>=1.2.33 : install a version greater than or equal to 1.2.33
<1.2.33 : install a version less than 1.2.33
<=1.2.33 : install a version less than or equal to 1.2.33
^1.2.33 : install any greater or equal compatible version with the same MAJOR number—such as 1.3.0 but not 2.0.0 (this is the default)
~1.2.33 : similar to ^ but won’t go beyond the next MINOR number—that is, a maximum of 1.3.0
* (or an empty string): install any version

Versions can be combined—for example, <2.0.0 || >=3.0.0 , to skip version 2.x.x

The installation of each package (and subpackage) is recorded in package-lock.json . This ensures subsequent installs are identical regardless of available updates.
The file can be added to your code repository, although you can run into problems if the application is installed on different operating systems. Personally, I prefer
to set the exact version in package.json , omit package-lock.json from the Git repo, and then update and test manually whenever new packages are available.

npm scripts
===========
The "scripts" section of package.json lists useful script aliases you can run during development, testing, building, deployment, and so on. A script is useful when you find yourself repeatedly retyping the same command.

For example: Consider the JavaScript bundler Rollup, which can build a single optimized client-side JavaScript file from multiple source files. The command to compile a development build is long. For example:
npx rollup --config --environment NODE_ENV:development --sourcemap --watch --no-watch.clearScreen, so we can create a script for it.
"scripts": {
  "rollup": "rollup --config --environment NODE_ENV:development --sourcemap --watch --no-watch.clearScreen"
}
npm run rollup


Pre and Post Scripts
Any script can have one or both of these:
a "pre<name>" script, which automatically runs before "<name>"
a "post<name>" script, which automatically runs after "<name>"
example:
"scripts": {
  "prebuild": "rm -rf build",
  "build": "rollup --config",
  "postbuild: "echo build complete"
}
npm run build (will run all 3 scripts)

There are special script names to do specialized tasks. example:
start: to start your app (npm start, "run" command not required)
test: to test your app (npm start)
stop: to stop your app (npm stop)

prepare:
prepublish:
prepublishOnly:
prepack:
postpack: (All these scripts run automatically when a package is required to be published)

One script can also use another script. Example:
"scripts": {
  "clean": "rm -rf build",
  "build:html": "sitegen ./src/content/ ./build/ --compress",
  "build:css": "cssgen ./src/css/main.css --out ./build/css/",
  "build:js": "jsgen ./src/js/main.js ./build/js/main.js --minify"
  "build": "clean && (build:html & build:css & build:js)" # will run clean followed by build.html/css/js in parallel)
}