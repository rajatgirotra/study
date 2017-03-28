#include <string>

extern std::string world();

std::string goodbye() {
    auto value = world();
    return value + ".. Goodbye ";
}
