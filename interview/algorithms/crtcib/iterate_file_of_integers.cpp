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
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>
#include <sstream>
#include <fstream>
#include <cassert>
using namespace std;

class Solution {
    private:
        std::istream& m_is;

    public:
        explicit Solution(istream& arg) : m_is(arg) {}

        class iterator;

        struct iterator {
            using iterator_category = std::input_iterator_tag;
            using value_type = int;
            using difference_type = std::ptrdiff_t;
            using pointer = void;
            using reference = void;
            private:
            std::reference_wrapper<std::istream> m_is;
            int m_val{};
            bool m_is_end {false};
            public:
            explicit iterator(istream& arg, bool is_end=false) : m_is(arg), m_is_end(is_end) {}
            int operator *() const noexcept { return m_val; }

            iterator& operator ++ () {
                istringstream ss;
                char buffer[11] {};
                // set exception on stringstream if parsing fails
                ss.exceptions(ios_base::failbit | ios_base::badbit);
                while(m_is.get().good()) {
                    // extract a line and put it in istringstream
                    m_is.get().getline(buffer, 11);
                    if(m_is.get()) {
                        ss.str(buffer);
                        try {
                            // try to extract integer
                            ss >> m_val;
                            // integer extracted but eof may be set. if eof gets set, this is a valid integer, otherwise not
                            if(ss.eof()) {
                               // a valid integer
                               ss.clear();
                               break;
                            }
                        } catch(...) {
                            // failed to extract. handle error cases
                            if(ss.bad()) {
                                cerr << "Unrecoverable error on stream\n";
                                m_val = -1;
                            } else if (ss.fail()) {
                                // not an integer, clear fail bit and try again
                                ss.clear();
                            } else {
                                // some other unknown error
                                cerr << "Unknown error\n";
                                m_val = -1;
                            }
                        }
                    }
                }
                return *this;
            }

            iterator& operator ++ (int) {
                return this->operator++();
            }

            bool operator == (const iterator& rhs) const noexcept {
                if((rhs.m_is_end && this->m_is_end) ||
                        (!rhs.m_is_end && !this->m_is_end)) {
                    return true;
                } else {
                    return m_is.get().eof();
                }
            }
            bool operator != (const iterator& rhs) const noexcept {
                return !this->operator == (rhs);
            }

        };

        iterator begin() {
            iterator it(m_is);
            m_is.seekg(0);
            ++it;
            return it;
        }

        iterator end() {
            iterator it(m_is, true); // is end iterator
            return it;
        }

};

int main() {
    fstream fis("/cygdrive/c/Users/rajat/Downloads/study/interview/algorithms/integers.txt");
    Solution sol(fis);
    for(Solution::iterator it = sol.begin(); it != sol.end(); ++it) {
        int x = *it;
        cout << x << endl;
    }
}
