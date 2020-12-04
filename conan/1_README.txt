Its a C/C++ package manager. Much like conda. You need python3 to use conan.

pip3 install conan
usually gets installed under $HOME/.local,
      
export CONAN_USER_HOME=$HOME/.local
export PATH=$CONAN_USER_HOME/bin:$PATH

Do "conan --help" to confirm

conan support packages for a wide variety of AOL (ie Archirecture, OS, Linker) like Windows/Linux, gcc, Intel, clang, Visual Studio etc.

remote repositories
===================
this is the location of the remote repositories which houses all of the pre-built c/c++ libraries and binaries.
common libraries and binaries like gcc, boost, openssl, poco etc are available for many common combinations of AOL (ie Archirecture, OS and Linker).if a pre-built package is not available, conan can also download the source and build it for you based on your host AOL.
The default repository is called ConanCenter (http://conan.io/center)

profiles
========
a profile contains settings that tells conan how to build conan packages from source if a pre-built package is not available for your AOL.
you can have as many profiles as you want. conan can build a default profile for you when you initialize conan for the first time.

Initializing conan
=================
the first thing you should do after installing conan is generate default configuration, using "conan config init"
This will create conan.conf, remotes.json, settings.yml, version.txt, profiles folder etc in $HOME/.local/.conan

