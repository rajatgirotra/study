Jar files in java are just zipped files which contain java class files together with other data like images, audio, video, config, scripts etc required to run a java application.
JDK has a tool called jar which is used to create/update/view/modify jar files.
Each jar file also has a manifest file (kind of meta-data file) containing information about the contents of the file and how the jar file should be used.
the file is always META-INF/MANIFEST.MF
Each jar file contains the time of creation also inside the jar file, so two jar files with identical files will not be equal. Always rely on the version information in
the jar manifest file.

Creating a jar file
===================
jar cf <jar_file_name> <input-files>
c means create
f means filename (i.e. jar file name)
There are other options also you can use
v means verbose
0 (zero) means do not compress files (may be used when you are streaming jar file over internet as compression-decompression make take time. Just that jar file might be little big).
m means you need to specify another file. The contents of this file will be merged with the META-INF/MANIFEST.MF created by the jar command. This file must have a blank line at the end.
Some other options are also there.

Default Contents of Manifest file (key value file separated by colon)
=====================================================================
Manifest-Version: 1.0
Created-By: 1.7.0_06 (Oracle Corporation)

You can do many things with a jar file. Lets see one by one.

Setting Application Entry Point
================================
java can invoke the public static void main(String[] args) function inside a class file in the jar if you set the application entry in the manifest file. You need to set
the Main-Class key. Example:
Main-Class: mypackage/mySuperDuperClass.class

you can do it using the "jar cvfm <jar_file> <manifest.txt> <input-files>" command, where manifest.txt contains the Main-Class key.
you can also use the "jar cfe app.jar MyApp MyApp.class" (i.e. e option). This overrides the Main-Class already defined in the manifest file if any.
You can then just run the application directly using "java -jar <jar_file>"

jar cfe app.jar foo.MyApp foo/MyApp.class # if the entry point is inside a package.

Setting Application Entry Point
================================