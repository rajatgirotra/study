/* First lock free program using C++11 atomics */
/*
 * I'll create two threads, one for SetItem and one for GetItem.
 * SetItem - will insert a key value pair linearly in an Array
 * GetItem - will linearly search for a value based on a key.
 *
 * If I use locks, I'll need to use a mutex to achieve mutual exclusion.
 * But here we do not use any locks.
 */

#ifndef _15_H_
#define _15_H_

#include <atomic>
#include <cstdint>
using namespace std;

//definition of each item
class ArrayOfItems
{
    private:
        struct Entry
        {
            atomic<int32_t> key;
            atomic<int32_t> value;
        };

        uint32_t m_size;
        Entry* m_entries;

    public:
        //c'tor
        ArrayOfItems(uint32_t size);
    
        //d'tor
        ~ArrayOfItems();

        void    setItem(int32_t key, int32_t value);
        int32_t getItem(int32_t key) const;
        uint32_t getItemCount() const;
        void    clear();
};

#endif //_15_H_

/*
 * Constraints:
 *
 * setItem is lock-free
 * getItem is wait-free
 * key = 0, means entry is not initialised.
 * You cannot store 0 as key or value
 * Size of array is prefixed ahead of time
 * You can Clear the array, but only at a time when there are no other calls being made from other threads.
 */


