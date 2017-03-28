--implicit-cache option

What Scons does is that it reads each dependancy to find out its implicit dependencies. i.e a list of include files in that file.
This though does not take much time but sometimes can get a bit annoying.

You can force scons to cache all these dependencies so that it is faster from second time onwards. You do this using
--implicit-cache option. However, if any dependency file changes, scons will read it again and update its cache. However, still it can sometimes cause a problem:

1) Let say the CPPPATH variable changes to include another file with the same name as was previously included. This will not be detected by scons and scons will not rebuild the file.

Sometimes when you run into some strange problems because of --implicit-cache options, it can be worth using the
--implicit-deps-changed option to force scons to rebuild all cache.


