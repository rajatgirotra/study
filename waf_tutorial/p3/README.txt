in the wscript file
1) top = . --> means the top level source directory of your project.
2) out = 'build' --> means the directory where all configuration files will be created and also build files will be written; like *.o, *.so *.a etc

waf configure --> will create the "build" directory
cd src
waf ping --> the output is important. Note that once you run waf configure, you can run waf from any subfolder of your project. waf will always run the command as if running waf from the same directory as the directory where you ran "waf configure"

waf dist --> bydefault it creates a noname-1.0.tar.bz2. You can control it either by providing global attributes APPNAME and VERSION or you can also control it in the dist(ctx) method. like specifying the appname, version, zip/tar/gz/bz2 , which files to add or exclude from your distribution.

waf distclean --> will remove the build directory completely

