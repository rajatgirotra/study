#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// see how try_emplace guarantees that it will be a no-op if key already exists in map.
// insert, emplace
using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::unordered_map<string, std::unique_ptr<int>> m;

    auto up_int = std::make_unique<int>(42);
    auto [it, result] = m.insert(std::make_pair("Rajat", std::move(up_int)));
    cout << result << endl;

    auto up_int2 = std::make_unique<int>(42);
    cout << "is up_int2 valid before insert: " << (up_int2 ? true : false) << endl;
    auto [it2, result2] = m.insert(std::make_pair("Rajat", std::move(up_int2)));
    cout << result2 << endl;
    cout << "is up_int2 valid after insert: " << (up_int2 ? true : false) << endl;

    auto up_int3 = std::make_unique<int>(42);
    cout << "is up_int3 valid before insert: " << (up_int3 ? true : false) << endl;
    auto [it3, result3] = m.emplace(std::make_pair("Rajat", std::move(up_int3)));
    cout << result3 << endl;
    cout << "is up_int3 valid after insert: " << (up_int3 ? true : false) << endl;

    auto up_int4 = std::make_unique<int>(42);
    cout << "is up_int4 valid before insert: " << (up_int4 ? true : false) << endl;
    auto [it4, result4] = m.try_emplace("Rajat", std::move(up_int4));
    cout << result4 << endl;
    cout << "is up_int4 valid after insert: " << (up_int4 ? true : false) << endl;

    auto&& up_int5 = m["Vidhu"]; // up_int5 is default constructed. So it's not managing anything.
    cout << "is up_int5 valid after insert: " << (up_int5 ? true : false) << endl;

}