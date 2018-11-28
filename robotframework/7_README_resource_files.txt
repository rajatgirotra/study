What are Resource Files
======================
Very simple. They are very similar to test cases files. Just that they cannot have test cases tables. They can only have Settings, Keywords, Variables tables. A resource file can also import other libraries and variable files in the settings table. All the keywords and variables in the resource files are available in the importing file. If two or more keywords have the same name, the keyword must be prefixed with the resource file name when you want to use it. If more than one variables have the same name, then the value which is imported first will prevail.

Where Robot looks up resource files
==================================
Resource file locations can be specified in the Settings table as absoulute or relative. If absoulute location is given, it is used as such. If location is relative, it is considered relative to the importing file. If file is still  not found, it is searched in the Python module search path. 
