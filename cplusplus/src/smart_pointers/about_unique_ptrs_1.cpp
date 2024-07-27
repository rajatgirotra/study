#include <iostream>
#include <memory>
using namespace std;

/*
 * interface for std::unique_ptr is very trivial.
 * template <typename T, typename Deleter = std::default_delete<T>>
 * class unique_ptr;
 *
 * Deleter should be a Callable which can be Copied. It could be a lambda, function object, function ptr etc.
 * the default deleter is very trivial and calls delete on the underlying pointer.
 *
 * template <typename T>
 * struct std::default_delete {
 *    void operator() (T* p) const {
 *        delete p;
 *     }
 * };
 *
 * Also, since C++11 there exists a partial specialization for std::unique_ptr where T = T[]. i.e. the underlying pointer is a pointer
 * to an array of type T.
 * template <typename T, typename Deleter>
 * struct unique_ptr<T[], Deleter>;
 *
 * Deleter will by default be std::default_delete<T> and since T is T[], default will be std::default_delete<T[]>
 * We have a partial specialization for std::default_delete<T[]> which calls delete[] instead of delete.
 *
 * the T[] partial specialization of unique_ptr also provides an index operator function to access the i-th element in the
 * underlying array.
 *
 * Since C++14, make_unique<> function were provided to have a consistent way to create smart pointers.
 *
 * template <typename T, typename... Args>
 * std::unique_ptr<T> make_unique(Args&&... args) {
 *     return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
 * }
 *
 * template <typename T>
 * std::unique_ptr<T> make_unique(size_t N); // only available of T is T[]. The elements of the array are value initialized.
 *
 * C++20 introduces two new make_* functions.
 * template <typename T>
 * std::make_unique_for_overwrite(); // for non array types
 *
 * template <typename T>
 * std::make_unique_for_overwrite(size_t N); // only for array types
 *
 * These functions perform default initialization and not value initialization. default initialization means only allocate memory
 * and do not perform any initialization. This might be needed if you are going to perform your own initialization right after
 * creating the unique_ptr<>, so using std::make_unique<>() and performing value initialization is waste some.
 *
 * There is also an added enhancement to std::unique_ptr<> that if the deleter is stateless, the size of the unique_ptr class will be
 * size of pointer only. It achieves it using Empty Base Class Optimization technique. An example:
 *
 * template <typename T, typename Deleter = std::default_delete<T>>
 * class unique_ptr {
 * private:
 *    class PtrAndDeleter : Deleter {
 *        public:
 *        T* m_ptr;
 *    };
 *
 *    PtrAndDeleter m_data;
 *
 *    unique_ptr(T* p = nullptr, Deleter d = Deleter()) : m_data(p, d) {}
 *    ~unique_ptr() {
 *        if (m_data.m_ptr) {
 *            static_cast<Deleter&>(m_data)(m_data.m_ptr);
 *        }
 *    }
 * };
 */

int main() {

}
