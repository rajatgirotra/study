/* reverse integer. If reversed integer doesnt fit in 32 bits, return 0.
  remember that bit 31 is signed bit, so bits 0-31 are used to represent value. So range would be -2^31 to (2^31)-1
*/

#include <iostream>
#include <cstdint>
#include <charconv>
#include <cassert>
#include <cstring>
#include <limits>
using namespace std;

int main(int argc, char** argv) {
    assert(argc == 2);
    int64_t value;
    int32_t max = std::numeric_limits<int32_t>::max();
    int32_t min = std::numeric_limits<int32_t>::min();
    auto [ptr, ec] {std::from_chars(argv[1], argv[1] + strlen(argv[1]), value, 10)};
    if(ec == std::errc()) {
        int32_t res = 0;
        while(value != 0) {
            auto digit = value % 10;
            value /= 10;

            // check
            if((res > max/10) || (res == max/10 && digit > max%10)) {
               res = 0;
               break;
            }
            else if ((res < min/10) || (res == min/10 && digit < min%10)) {
               res = 0;
               break;
            }
            res = (res*10) + digit;
        }
        cout << "Reversed integer: " << res << endl;
    } else if (ec == std::errc::invalid_argument)  {
        cout << "Argument is not a number. Cannot reverse!\n";
        exit (-1);
    } else if(ec == std::errc::result_out_of_range) {
        cout << "Argument is too big to fit in int64_t type\n";
        exit (-1);
    }
}
