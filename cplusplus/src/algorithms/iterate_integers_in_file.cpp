/*
 * Write an iterator to iterate over a file of integers. one integer per line.
 * Lines containing non integers should be skipped
 * The iterator will only be used once.
 * Example:
 *  integers.txt
 *  137
 *  -104
 *  2 58
 *  +0
 *  ++3
 *  +1
 *  23.9
 *  2000000000
 *  -0
 *  five
 *  -1
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <memory>
#include <iomanip>
#include <cassert>
#include <limits>
#include <optional>
#include <sstream>
#include <cmath>
using namespace std;

class Solution {
    std::ifstream& m_ifs;

public:
    Solution(std::ifstream& ifs) noexcept: m_ifs(ifs) {}

    class iterator {
    public:
        using iterator_category_tag = std::input_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int&;

    private:
        std::reference_wrapper<std::ifstream> m_ifs;
        bool m_is_end = false;
        int m_value{};

    public:
        iterator(std::ifstream& ifs, bool isEnd = false) noexcept : m_ifs(ifs), m_is_end(isEnd) {
            auto& file_is = m_ifs.get();
            assert(file_is.is_open());
        }

        int operator* () {
            return m_value;
        }

        iterator(const iterator& other) noexcept = default;

        bool operator == (const iterator& other) const noexcept {
            return ((m_is_end == true && other.m_is_end == true) ||
                    (!m_is_end && !other.m_is_end && m_ifs.get().tellg() == other.m_ifs.get().tellg()));
        }

        bool operator != (const iterator& other) const noexcept {
            return !this->operator==(other);
        }

        iterator& operator = (const iterator& other) noexcept {
            m_ifs = other.m_ifs;
            return *this;
        }

#if 0
        iterator& operator ++ () noexcept {
            auto& file_is = m_ifs.get();
            while(!m_is_end && file_is.good()) {
                int num{};
                file_is >> num;
                m_value.emplace(num);
                // if failed to read an integer, skip the line, and clear the state
                if(file_is.fail()) {
                    if(file_is.eof()) break;
                    file_is.clear();
                    file_is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                } else {
                    return *this;
                }
            }
            // reached end of file
            m_is_end = true;
            return *this;
        }
#endif

        //not perfect but works. doesnt work when there is no newline at the end of file
        iterator& operator ++ () noexcept {
            auto&& file_is = m_ifs.get();
            stringstream ss;
            char buffer[11] {};
            // set exception on stringstream if parsing fails
            ss.exceptions(ios_base::failbit | ios_base::badbit);
            while(file_is.good()) {
                ss.clear();
                file_is.getline(buffer, 11);
                if(file_is.bad()) {
                    cout << "Unrecoverable error reading file\n";
                    exit(-1);
                } else if(file_is.fail()) {
                    // nothing read. we are done.
                    m_is_end = true;
                    m_value = -1;
                    break;
                }
                ss.str(buffer);
                try {
                    ss >> m_value;
                    if(ss.eof()) {
                        break;
                    }
                } catch(...) {
                    if(ss.bad()) {
                        cout << "Unrecoverable error parsing integer\n";
                        exit(-1);
                    } else if (ss.fail()) {
                        // not an integer. clear the state and continue to read next line
                        continue;
                    }
                }
            }

            if(file_is.eof()) {
                m_is_end = true;
                m_value = -1;
            }
            return *this;
        }

        iterator& operator ++ (int) noexcept {
            return this->operator++();
        }
    };

    iterator begin() {
        iterator it(m_ifs);
        m_ifs.seekg(0, std::ios::beg);
        ++it;
        return it;
    }

    iterator end() {
        return iterator(m_ifs, true);
    }
};

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>\n";
        exit(-1);
    }

    ifstream file_is(argv[1], std::ios_base::in);
    assert(file_is.is_open());

    Solution sol(file_is);
    for(auto iter = sol.begin(); iter != sol.end(); ++iter) {
        cout << *iter << endl;
    }
}