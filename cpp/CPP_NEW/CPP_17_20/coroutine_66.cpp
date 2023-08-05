/* first coroutine */

#include <iostream>
#include <coroutine>
#include <exception>
using namespace std;

// coroutine interface that the caller of coroutine will use to deal with the coroutine.
// why [[nodiscard]] --> If the caller will not capture the return type, how in the world will he deal with
// the coroutine?  It is basically to catch bugs where developers might accidentally treat coroutines as normal
// functions and ignore their return value.
struct [[nodiscard]] CoroTask {
    struct promise_type;
    using CoroHdl = std::coroutine_handle<promise_type>;
    private:
        CoroHdl m_handle;

    public:
        // ctor and dtor
        explicit CoroTask(auto handle) : m_handle(handle) {}
        ~CoroTask() {
            if(m_handle) {
                m_handle.destroy(); // must always destroy the coroutine frame on memory.
            }
        }    
        
        // disable copy and move to keep things simple
        CoroTask(const CoroTask&) = delete;
        CoroTask(CoroTask&&) = delete;

        bool resume() noexcept {
            // if handle is nullptr of if coroutine has already completed, return false.
            if(!m_handle || m_handle.done()) {
                return false;
            }

            // use the native coroutine API to resume the coroutine.
            m_handle.resume(); // or m_handle() (because function call operator is overloaded to call resume())
            return !m_handle.done();
        }
};

struct CoroTask::promise_type {
    auto get_return_object() {
        return CoroTask{CoroTask::CoroHdl::from_promise(*this)};
    }

    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }

    void unhandled_exception() { std::terminate(); }
    void return_void() {}
};

CoroTask coro(int max) {
    cout << "\tcoro " << max << " start\n";

    for(int i = 1; i <= max; ++i) {
        cout << "\tcoro " << i << "/" << max << "\n";
        co_await std::suspend_always{}; // suspend point
    }

    cout << "\tcoro " << max << " end\n";
}

int main() {
    auto task = coro(5);
    cout << "coro() created\n";

    // loop through coroutine until resume() is true
    while(task.resume()) {
        cout << "coro() suspended\n";
    }
    cout << "coro() done\n";
}

/* Next we will call a coroutine inside an other coroutine */

/* A word on final_suspend()
 * This function is called by the coroutine frame outside the try block that encloses the coroutine body after return_void(), return_value(),
 * or unhandled_exception() is called. Because final_suspend() is outside the try block, it has to be noexcept.
 *
 * The name of this member function is a little misleading because it gives the impression that you could also return std::suspend_never{} here to
 * force one more resumption after reaching the end of the coroutine. However, it is undefined behavior to resume a coroutine that is really suspended at
 * the final suspend point. The coroutine has already returned its finally value so there is no point in resuming now.
 * The only thing you can do with a coroutine suspended here is destroy it. Therefore, the real purpose of this member function is to execute some logic,
 * such as publishing a result, signaling completion, or resuming a continuation somewhere else.
 *
 * So almost always you will return std::suspend_always{}; in final_suspend()
 *
 * Also
 * When the handle is default initialized or nullptr is used as the initial or assigned value, the coroutine handle does not refer to any coroutine.
 * In that case, any conversion to a Boolean value yields false:
 * std::coroutine_handle<PrmType> hdl = nullptr;
 * if (hdl) will be false
 * Copying and assigning a coroutine handle is cheap. They just copy and assign the internal pointer. Therefore, coroutine handles are usually passed
 * by value.
 *
 * The address() function in coroutine_handle<> class yields the internal pointer of the coroutine as void*. This allows programmers to export the
 * coroutine handle to somewhere and later recreates a handle with the static function from_address():
 * auto hdl = std::coroutine_handle<decltype(prm)>::from_promise(prm);
 * ...
 * void* hdlPtr = hdl.address();
 * ...
 * auto hdl2 = std::coroutine_handle<decltype(prm)>::from_address(hdlPtr);
 * hdl == hdl2 // true
 * However, note that you can use the address only as long as the coroutine exists. After a coroutine has been destroyed, the address may be reused
 * by another coroutine handle.
 *
 * All coroutine handle types have an implicit type conversion to class std::coroutine<void>
namespace std {
template<typename Promise>
struct coroutine_handle {
...
// implicit conversion to coroutine_handle<void>:
constexpr operator coroutine_handle<>() const noexcept;
...
};
}
 */