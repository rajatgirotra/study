/*
 * You already know that size of int, long, etc are architecture  and machine dependent.
 * C++0x11 introduces a header file <cstdint> which includes types which are the same across all platforms and architectures.
 * std::int8_t is 1 byte
 * std::int16_t is 2 bytes
 * std::int32_t is 4 bytes
 * std::int64_t is 8 bytes
 *
 * You also have unsigned versions of these too.
 */

#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;

int main() {

	cout << "int8_t min: " << (int)numeric_limits<int8_t>::min() << endl;
	cout << "int8_t max: " << (int)numeric_limits<int8_t>::max() << endl;

	cout << "int16_t min: " << numeric_limits<int16_t>::min() << endl;
	cout << "int16_t max: " << numeric_limits<int16_t>::max() << endl;

	cout << "int32_t min: " << numeric_limits<int32_t>::min() << endl;
	cout << "int32_t max: " << numeric_limits<int32_t>::max() << endl;

	cout << "int64_t min: " << numeric_limits<int64_t>::min() << endl;
	cout << "int64_t max: " << numeric_limits<int64_t>::max() << endl;

	cout << "uint8_t min: " << numeric_limits<uint8_t>::min() << endl;
	cout << "uint8_t max: " << numeric_limits<uint8_t>::max() << endl;

	cout << "uint16_t min: " << numeric_limits<uint16_t>::min() << endl;
	cout << "uint16_t max: " << numeric_limits<uint16_t>::max() << endl;

	cout << "uint32_t min: " << numeric_limits<uint32_t>::min() << endl;
	cout << "uint32_t max: " << numeric_limits<uint32_t>::max() << endl;

	cout << "uint64_t min: " << numeric_limits<uint64_t>::min() << endl;
	cout << "uint64_t max: " << numeric_limits<uint64_t>::max() << endl;

	cout << "char min: " << (int)numeric_limits<char>::min() << endl;
	cout << "char max: " << (int)numeric_limits<char>::max() << endl;

	cout << "unsigned char min: " << (int)numeric_limits<unsigned char>::min() << endl;
	cout << "unsigned char max: " << (int)numeric_limits<unsigned char>::max() << endl;
	return 0;
}

/*
 * Note the strange output for int8_t and uint8_t. this is because int8_t is internally represented as a char, so the output is the corresponding ascii code and not the integer.
 * You can cast it to integer and then it will show the correct output.
 */
