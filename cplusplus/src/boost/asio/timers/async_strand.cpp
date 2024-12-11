/*
 * Call multiple CompletionHandlers on multiple threads (by calling io_context.run()) from each thread.
 * But internally all the completion handlers must be run sequentially on a strand object.
 */
#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>
#include <ranges>
#include <syncstream>
#include <array>
namespace asio = boost::asio;
namespace rng = std::ranges;
namespace vws = std::ranges::views;
using namespace std;

auto syncOut = [](std::ostream& os = std::cout) {
    return std::osyncstream {os};
};


int main() {
    asio::io_context io;
    constexpr int num_threads = 5;

    auto strand = asio::make_strand(io);

    auto now = std::chrono::steady_clock::now();
    auto expiry_time = now + 5s;

    std::array<std::shared_ptr<asio::steady_timer>, num_threads> timer;

    for([[maybe_unused]] auto i : vws::iota(0, num_threads)) {
        timer[i].reset(new asio::steady_timer(io, expiry_time));

        timer[i]->async_wait(asio::bind_executor(strand, [&](const boost::system::error_code ec) {
//            timer[i]->async_wait([&](const boost::system::error_code ec) {
            if(!ec) {
                syncOut() << "Wait over, thread id: " << this_thread::get_id() << ", Timer expired!\n";
            } else if (ec == asio::error::operation_aborted) {
                syncOut() << "Wait over, thread id: " << this_thread::get_id() << ", Timer cancelled!\n";
            } else {
                syncOut() << "Wait over, thread id: " << this_thread::get_id() << ", " << ec.message() << '\n';
            }
        }));
    }

    // the timer must outlive the Asynchronous operation. i.e. it must be valid till the CompletionHandler is called.
    // that's because the destructor of the timer cancels the asynchronous operation. So we create the timer using std::array of shared_ptr.

    auto threadArr = std::make_unique_for_overwrite<std::jthread[]>(num_threads);
    for(auto i : vws::iota(0, num_threads)) {
        threadArr[i] = std::jthread([&io] {
            io.run();
        });
    }
}

/*
 * Without using asio::bind_executor, by default the CompletionHandlers will run on the system_executor which runs an arbitrary thread pool.
 * the asio::bind_executor(strand, CompletionHandler) encapsulates the CompletionHandlers returns a new CompletionHandler.
 * which has the "executor_type" typedef and the get_executor() method defined. so the default associated_executor will find the strand executor which internally
 * serializes the CompletionHandlers.
 */