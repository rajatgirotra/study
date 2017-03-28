Very simple. Doxygen reads a config file and can generate HTML documentatin, PDF and some other formats.
Main executable is doxygen. 

doxygen -g <configFile> will produce a default config. Best is to edit it.
Eg: doxygen -g Doxyfile

The config file is nothing but tag=value pairs. To run doxygen, just say
doxygen <configFile>

There is also a GUI interface (use doxywizard) to start it. It allows you to modify config file in GUI and 
also run doxygen to generate documentation.


