#include <iostream>
#include <thread>
#include <string>
#include <semaphore.h>
#include <random>
#include <functional>
#include <errno.h>
#include <cstdlib>
#include <limits>

#ifdef USE_SINGLE_HW_THREAD
    #include <sched.h>
#endif

using namespace std;
sem_t begin_1_sema, begin_2_sema, end_sema;
unsigned int X = 0, Y = 0, R1 = 0, R2 = 0;

// ##################################### START RANDOM NUMBER GENERATOR #################################################
//-------------------------------------
//  MersenneTwister
//  A thread-safe random number generator with good randomness
//  in a small number of instructions. We'll use it to introduce
//  random timing delays.
//-------------------------------------
#define MT_IA  397
#define MT_LEN 624

class MersenneTwister
{
    unsigned int m_buffer[MT_LEN];
    int m_index;

public:
    MersenneTwister(unsigned int seed);
    // Declare noinline so that the function call acts as a compiler barrier:
    unsigned int integer() __attribute__((noinline));
};

MersenneTwister::MersenneTwister(unsigned int seed)
{
    // Initialize by filling with the seed, then iterating
    // the algorithm a bunch of times to shuffle things up.
    for (int i = 0; i < MT_LEN; i++)
        m_buffer[i] = seed;
    m_index = 0;
    for (int i = 0; i < MT_LEN * 100; i++)
        integer();
}

unsigned int MersenneTwister::integer()
{
    // Indices
    int i = m_index;
    int i2 = m_index + 1; if (i2 >= MT_LEN) i2 = 0; // wrap-around
    int j = m_index + MT_IA; if (j >= MT_LEN) j -= MT_LEN; // wrap-around

    // Twist
    unsigned int s = (m_buffer[i] & 0x80000000) | (m_buffer[i2] & 0x7fffffff);
    unsigned int r = m_buffer[j] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
    m_buffer[m_index] = r;
    m_index = i2;

    // Swizzle
    r ^= (r >> 11);
    r ^= (r << 7) & 0x9d2c5680UL;
    r ^= (r << 15) & 0xefc60000UL;
    r ^= (r >> 18);
    return r;
}
// ##################################### END RANDOM NUMBER GENERATOR ###################################################

#define handle_error(msg) \
do { perror(msg); exit(-1); } while(0);

void thread_one() noexcept {
    MersenneTwister random(1);
    do {
        sem_wait(&begin_1_sema);
        // random delay
        while(random.integer() % 8 != 0) {}
        X = 1; // STORE
#ifdef USE_CPU_FENCE
asm volatile("mfence" ::: "memory");
#elif USE_SINGLE_HW_THREAD
asm volatile("" ::: "memory");
#endif
        R1 = Y; // LOAD FROM A DIFFERENT LOCATION.
        sem_post(&end_sema);
    } while(1);
}

void thread_two() noexcept {
    MersenneTwister random(2);
    do {
        sem_wait(&begin_2_sema);
        // random delay
        while(random.integer() % 8 != 0) {}
        Y = 1; // STORE
#ifdef USE_CPU_FENCE
asm volatile("mfence" ::: "memory");
#elif USE_SINGLE_HW_THREAD
asm volatile("" ::: "memory");
#endif
        R2 = X; // LOAD FROM A DIFFERENT LOCATION.
        sem_post(&end_sema);
    } while(1);
}

int main() {
    unsigned int iteration_count {};
    unsigned int reorder_count {};

    // init semaphores
    if(sem_init(&begin_1_sema, 0, 0) != 0)
        handle_error("sem_init begin_1_sema");

    if(sem_init(&begin_2_sema, 0, 0) != 0)
        handle_error("sem_init begin_2_sema");

    if(sem_init(&end_sema, 0, 0) != 0)
        handle_error("sem_init end_sema");

    // start the two thread
    auto t1 = std::thread(std::cref(thread_one));
    auto t2 = std::thread(std::cref(thread_two));

#ifdef USE_SINGLE_HW_THREAD
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(1, &cpus);
    if(pthread_setaffinity_np(t1.native_handle(), sizeof(cpus), &cpus) != 0)
        handle_error("pthread_setaffinity_np");
    if(pthread_setaffinity_np(t2.native_handle(), sizeof(cpus), &cpus) != 0)
        handle_error("pthread_setaffinity_np");
#endif

    do {
        X = Y = R1 = R2 = 0;
        if(sem_post(&begin_1_sema) != 0)
            handle_error("sem_post begin_1_sema");
        if(sem_post(&begin_2_sema) != 0)
            handle_error("sem_post begin_2_sema");
        if(sem_wait(&end_sema) != 0)
            handle_error("sem_wait end_sema");
        if(sem_wait(&end_sema) != 0)
            handle_error("sem_wait end_sema");

        ++iteration_count;
        // check re-ordering
        if (R1 == 0 && R2 == 0) {
            ++reorder_count;
            cout << reorder_count << " reorders in " << iteration_count << " iterations.\n";
        }
    } while(iteration_count < std::numeric_limits<decltype(iteration_count)>::max()-10);

    t1.join();
    t2.join();

    return 0;

}
