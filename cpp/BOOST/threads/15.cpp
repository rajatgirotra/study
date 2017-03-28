/*
   Barrier - Another concept is barrier. Very simple. It has a c'tor which takes an integer argument (say n) to initialise the barrier object. All threads using the barrier object and
   calling wait() function will block. When the last thread (n-th thread) calls wait(), all n threads will unblock.

   include boost/thread/barrier.hpp
 */

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

//We will create 10 threads, nine of which will call wait() almost instantaneously, but one will sleep for 10 seconds before calling wait.

static boost::barrier* poBarrier = 0 ;
boost::mutex mut;

void function(int wait_duration = 1) {
    boost::this_thread::sleep(seconds(wait_duration));
    mut.lock();
    cout << "Thread " << boost::this_thread::get_id() << " waiting" << endl;
    mut.unlock();

    poBarrier->wait();

    mut.lock();
    cout << "Thread " << boost::this_thread::get_id() << " past the barrier point" << endl;
    mut.unlock();
}

int main() {

    poBarrier = new boost::barrier(10);
    
    boost::thread t1(&function, 1);
    boost::thread t2(&function, 1);
    boost::thread t3(&function, 1);
    boost::thread t4(&function, 1);
    boost::thread t5(&function, 1);
    boost::thread t6(&function, 1);
    boost::thread t7(&function, 1);
    boost::thread t8(&function, 1);
    boost::thread t9(&function, 1);
    boost::thread t10(&function, 10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    delete poBarrier;

    return 0;
}

/*
 * Note that here boost::mutex is simply used to synchronize output to the standard console.
 * Otherwise the ouput will be garbled.
 */
