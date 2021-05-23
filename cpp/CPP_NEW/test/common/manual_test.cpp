#include "common/Singleton.hpp"
#include <iostream>
using namespace cs::common;
using namespace std;

class Integer : public Singleton<Integer> {
    friend class Singleton<Integer>;
    int m_value{100};
protected:
    Integer() = default;
public:
    int getValue() const noexcept { return m_value; }
    void setValue(int arg) noexcept { m_value = arg; }

};

int main() {
    [[maybe_unused]] Integer& instance = Integer::instance();
    instance.setValue(99);
    Integer& ins = Integer::instance();
    cout << ins.getValue() << endl;
}
