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
