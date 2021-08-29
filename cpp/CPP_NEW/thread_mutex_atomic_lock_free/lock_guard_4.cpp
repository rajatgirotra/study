/*
 * Very simple RAII over std::mutex. std::unique_guard constructor locks the mutex and destructor unlocks it
 * Also has another ctor which doesn't lock but just adopts it. so that the destructor will call unlock.
 */
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <string>

using namespace std;
class bank_account {
private:
    string m_name;
    int m_balance {};
public:
    mutable std::mutex m_mutex;
    explicit bank_account(const string& name, int arg) : m_name(name), m_balance(arg) {}

    void add_balance(int arg) { m_balance += arg; }

    int balance() const noexcept { return m_balance; }
    const string& name() const noexcept { return m_name; }

    friend ostream& operator << (ostream& os, const bank_account& rhs) {
        return os << "AccountName: " << rhs.m_name << ", balance: " << rhs.m_balance;
    }
};

void xfer(bank_account& from, bank_account& to, int amount) {
    //lock mutex for both accounts to avoid deadlock
    std::lock(from.m_mutex, to.m_mutex);

    // initiate xfer
    std::lock_guard<std::mutex> lg_from(from.m_mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lg_to(to.m_mutex, std::adopt_lock);

    from.add_balance(-amount);
    to.add_balance(amount);
}

int main() {
    bank_account rajat("Rajat", 100);
    bank_account vidhu("Vidhu", 100);
    cout << "Balance before xfer\n";
    cout << rajat << endl;
    cout << vidhu << endl;

    // initiate two xfers.
    std::thread t1(std::ref(xfer), std::ref(rajat), std::ref(vidhu), 50);
    std::thread t2(std::ref(xfer), std::ref(vidhu), std::ref(rajat), 150);

    t1.join();
    t2.join();
    cout << "Balance after xfer\n";
    cout << rajat << endl;
    cout << vidhu << endl;
}
