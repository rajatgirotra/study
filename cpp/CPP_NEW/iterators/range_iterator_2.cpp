/*
 * Create a template class Range which takes two template parameters of integral type: FROM and TO
 * Create an iterator of this class which goes from FROM to TO, both FROM and TO are inclusive and if FROM > TO,
 * you go iterate in reverse order.
 */

#include <iostream>
#include <algorithm>
using namespace std;

template <long FROM, long TO>
class Range {
public:
    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = long;
        using difference_type = long;
        using pointer = long*;
        using reference = long;

        explicit constexpr iterator(long arg) : mIterValue(arg) {}
        reference operator *() const {
            return mIterValue;
        }

        iterator& operator ++() {
            mIterValue = (FROM <= TO ? mIterValue+1 : mIterValue-1);
            return *this;
        }

        iterator operator ++ (int) {
            iterator ret(*this);
            ++(*this);
            return ret;
        }

        bool operator == (const iterator& rhs) const noexcept {
            return mIterValue == rhs.mIterValue;
        }

        bool operator != (const iterator& rhs) const noexcept {
            return !(*this == rhs);
        }
    private:
        long mIterValue {FROM};
    };

    iterator begin() {
        return iterator(FROM);
    }

    iterator end() {
        return iterator(TO >= FROM ? TO + 1 : TO-1);
    }
};

int main() {
    auto range = Range<25, 15>();

    // find 18 in range
    auto iter = std::find(range.begin(), range.end(), 18);
    cout << *iter << endl;

    // can also use Range::iterator in range based for loops.
    for(const auto& item : range) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}

/*
 * Please read Iterator_Categories_3.txt next
 */
