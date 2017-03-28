#include <string>

extern std::string hello();

std::string world() {
    auto value = hello();
    return value + " world";
}
