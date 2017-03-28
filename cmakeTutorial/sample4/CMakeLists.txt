cmake_minimum_required (VERSION 2.6)
project (Tutorial)

### The version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

## Configure a header file to pass some the CMake settings to source code.
configure_file (
	"TutorialConfig.h.in"
	"TutorialConfig.h"
)

include_directories(.)

add_executable(Tutorial tutorial.cpp)

