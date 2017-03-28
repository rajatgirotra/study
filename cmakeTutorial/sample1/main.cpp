#include <iostream>

#ifndef ABC
    #error ABC is not defined
#else
    #warning ABC is defined
#endif

#if FOO > 10
    #error foo is greater than 10
#else
    #warning foo is less than equal to 10
#endif

int main() {
	std::cout << "Good bye CMake" << std::endl;
	return 0;
}

