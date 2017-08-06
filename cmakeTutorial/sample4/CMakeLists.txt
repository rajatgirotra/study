cmake_minimum_required (VERSION 3.5.1)
project (Tutorial VERSION 1.2.3 LANGUAGES C CXX)

### The version number
#set (Tutorial_VERSION_MAJOR 1)
#set (Tutorial_VERSION_MINOR 0)

## Configure a header file to pass some the CMake settings to source code.
configure_file (
	"TutorialConfig.h.in"
	"TutorialConfig.h" ESCAPE_QUOTES NEWLINE_STYLE UNIX)

include_directories(.)

add_executable(Tutorial tutorial.cpp)

