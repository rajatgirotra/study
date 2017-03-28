set (roof_client_src main.cpp)
## Again define the roof_client_src variable as in the lib folder.

add_executable (main ${roof_client_src})
## create executable main

target_link_libraries(main roof)
## link with libroof.so

set_target_properties(main
		PROPERTIES OUTPUT_NAME roof)
##rename target main to roof.
## set_target_properties: Targets can have properties that affect how they are built.
##  set_target_properties(target1 target2 ...
##                       PROPERTIES prop1 value1
##                        prop2 value2 ...)
##Set properties on a target. The syntax for the command is to list all the files you want to change, and then provide the values you want to set next. You can use any prop value pair you want and extract it later with the GET_TARGET_PROPERTY command.

##Properties that affect the name of a target's output file are as follows. The PREFIX and SUFFIX properties override the default target name prefix (such as "lib") and suffix (such as ".so"). IMPORT_PREFIX and IMPORT_SUFFIX are the equivalent properties for the import library corresponding to a DLL (for SHARED library targets). OUTPUT_NAME sets the real name of a target when it is built and can be used to help create two targets of the same name even though CMake requires unique logical target names. 
