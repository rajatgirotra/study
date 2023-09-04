Installing nodejs
=================

i installed from binary package manager on ubuntu. A company called nodesource provides nodejs binary packages for ubuntu. Just ran this command.

curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash - &&\
sudo apt-get install -y nodejs

global package setup
===================
I setup a location $HOME/.npm-global and added $HOME/.npm-global/bin to $PATH. This is the location where npm (node package manager) will install node packages globally.
I did:

npm config set prefix $HOME/.npm-global
export PATH=${HOME}/.npm-global/bin:${PATH}

to install global packages use the --global/-g option (example: npm install eslint -g)

nodejs REPL
==========
just run node to start the nodejs REPL (Read, Execute, Print, Loop). You can play interactively with node here

next look at console_3 and server_4 javascripts.


Nodejs Global folder vs cache folder
====================================
Global folder: Global installs (using npm install --global) on Unix systems go to {prefix}/lib/node_modules. Global installs on Windows go to {prefix}/node_modules
Cache: Cache files are stored in ~/.npm on Posix, or ~/npm-cache on Windows

The npm cache is just an HTTP cache. All HTTP requests are cached, so if you do npm install it does not have to access the network if it finds the package in the cache. This is useful when you are creating docker containers during your build process, because it speeds up the build considerably. If you clear the cache - the very first time after that your npm install will be slower until the cache has a copy of the packages that you need. The cache is both filled and accessed during npm install. Also if you have multiple projects that use the same versioned npm packages there would be only a single copy in cache for those packages. So it is a productivity gain.