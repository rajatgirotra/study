#include <iostream>
#include <type_traits>

/* For scoped enums (ie enums with struct/class, the default underlying type is int)
 * For unscoped enums (c++ 98 enums), underlying type is implementation defined integral type that can hold
 * all enums defined */
using namespace std;
enum struct Color : char {
    RED,
    ORANGE,
    BLUE
};

enum class Fruit : int {
    BANANA,
    APPLE,
    ORANGE
};

enum unscoped_e1 {

};


int main() {
    bool color_type = std::is_same<char, std::underlying_type<Color>::type>::value;
    bool fruit_type = std::is_same<int, std::underlying_type<Fruit>::type>::value;
    bool e1_type = std::is_same<unsigned, std::underlying_type<unscoped_e1>::type>::value;

    cout << "Underlying type of Color is: " << (color_type ? "char" : "not char") << endl;
    cout << "Underlying type of Fruit is: " << (fruit_type ? "int" : "not int") << endl;
    cout << "Underlying type of unscoped enum e1 is: " << (e1_type ? "unsigned" : "not unsigned") << endl;
    return 0;
}



