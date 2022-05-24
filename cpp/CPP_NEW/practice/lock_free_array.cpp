#include <iostream>
#include <atomic>
#include <string>
#include <iomanip>
#include <cstdint>
#include <memory>
#include <cassert>
#include <random>
#include <thread>
#include <utility>
#include <mutex>
using namespace std;

class ArrayOfItems {
private:
    uint32_t m_size;
    struct Entry {
    public:
        std::atomic<int32_t> m_key {0};
        std::atomic<int32_t> m_value {0};
    };
    std::unique_ptr<Entry[]> m_entries;

public:
    explicit ArrayOfItems(uint32_t sz) : m_size(sz), m_entries(std::make_unique<Entry[]>(m_size)) {}
    ~ArrayOfItems();

    void setItem(int key, int value);
    int getItem(int key) const;
    uint32_t getItemCount() const;
    void clear();
    std::pair<int, int> getItemByIndex(uint32_t idx) const;
};

ArrayOfItems::~ArrayOfItems() {
    m_size = 0;
}

void ArrayOfItems::setItem(int key, int value) {
    // iterate over the array. Find an entry where probedKey is either 0 or equal to key.
    // if found, store given key in that location, and later store the value.
    assert(key != 0);
    assert(value != 0);
    for(auto index = 0ul; index < m_size; ++index) {
        auto probedKey = std::atomic_load_explicit(std::addressof(m_entries[index].m_key), std::memory_order_relaxed);
        if(probedKey != key) {
            if(probedKey != 0) {
                // This is some other entry. continue searching
                continue;
            } else {
                // found a free slot where key = 0, try to store key.
                auto x = 0;
                if(std::atomic_compare_exchange_strong_explicit(
                        std::addressof(m_entries[index].m_key), std::addressof(x), key,
                        std::memory_order_relaxed, std::memory_order_relaxed) == false) {
                    // another thread stole this index underneath us.
                    continue;
                } else {

                }
            }
        }
        // found the entry.
        std::atomic_store_explicit(std::addressof(m_entries[index].m_value), value, std::memory_order_relaxed);
        return;
    }
}

int ArrayOfItems::getItem(int key) const {
    assert(key != 0);
    for(auto index = 0ul; index < m_size; ++index) {
        auto probedKey = std::atomic_load_explicit(std::addressof(m_entries[index].m_key), std::memory_order_relaxed);
        if(probedKey == key) {
            auto value = std::atomic_load_explicit(std::addressof(m_entries[index].m_value), std::memory_order_relaxed);
            return value;
        } else if (probedKey == 0) {
            // no need to search further as rest of the items would be empty
            return 0;
        }
    }
    return 0;
}

std::pair<int, int> ArrayOfItems::getItemByIndex(uint32_t idx) const {
    assert(idx < m_size);
    auto probedKey = std::atomic_load_explicit(std::addressof(m_entries[idx].m_key), std::memory_order_relaxed);
    auto value = std::atomic_load_explicit(std::addressof(m_entries[idx].m_value), std::memory_order_relaxed);
    return std::make_pair(probedKey, value);
}


uint32_t ArrayOfItems::getItemCount() const {
    uint32_t index{};
    for(index = 0ul; index < m_size; ++index) {
        if((std::atomic_load_explicit(std::addressof(m_entries[index].m_key), std::memory_order_relaxed) == 0) ||
                (std::atomic_load_explicit(std::addressof(m_entries[index].m_value), std::memory_order_relaxed) == 0))
            return index;
    }
    return index + 1;
}

void ArrayOfItems::clear() {
    // not lock free
    for(auto index = 0ul; index < m_size; ++index) {
        m_entries[index].m_key = m_entries[index].m_value = 0;
    }
}
ArrayOfItems a(100000);

static std::default_random_engine generator;
static std::uniform_int_distribution<int> distribution(1, 100000);
std::mutex iomutex;
void setterThread()
{
    for(int i = 0; i < 100000; ++i)
    {
        auto k = distribution(generator);
        auto v = distribution(generator);
        std::lock_guard<std::mutex> _(iomutex);
        cout << "Setting " << k << " " << v << endl;
        a.setItem(k, v);
    }
}

void getterThread()
{
}

int main()
{

    std::thread tg1(getterThread);
    std::thread tg2(getterThread);
    std::thread ts1(setterThread);
    std::thread ts2(setterThread);

    tg1.join(); tg2.join();
    ts1.join(); ts2.join();

    for(uint32_t i = 0ul; i < 100000; ++i) {
        auto [k, v] = a.getItemByIndex(i);
        cout << "Index " << i << "  (k, v): " << k << " " << v << endl;
    }
    return 0;
}
