#include "15.h"
#include <thread>
#include <iostream>
#include <cassert>
#include <cstring>
#include <fstream>
using namespace std;

ofstream out("16.out");

ArrayOfItems::ArrayOfItems(uint32_t size) : m_size(size), m_entries(new Entry[m_size])
{
    clear();
}

ArrayOfItems::~ArrayOfItems()
{
    delete[] m_entries;
    m_size = 0;
}

void ArrayOfItems::clear()
{
    memset(m_entries, 0, sizeof(Entry) * m_size);
}

void ArrayOfItems::setItem(int32_t key, int32_t value)
{
    assert(key   != 0);
    assert(value != 0);
    //First iterator linearly through the array and search for a free spot.
    for(uint32_t index = 0; index < m_size; ++index)
    {
        //Fetch key from this index.
        int32_t probedKey = atomic_load_explicit(&m_entries[index].key, memory_order_relaxed);
      
        if(probedKey != key)
        {
            if(probedKey != 0)
                continue; //This is someother key slot, continue probing

            //This entry is free. do compare and exchange to store the new key.
            int32_t expected = 0;
            if(atomic_compare_exchange_strong_explicit(&m_entries[index].key, &expected, key, memory_order_relaxed, memory_order_relaxed))
            {
                //out << "Setter: Saved key [" << key << "] by thread [" << std::this_thread::get_id() << "]" << endl;
                ;
            }
            else
            {
                //Another thread just stole it from underneath us.
                //out << "Setter: Another thread just stole or chance to save key [" << key << "] by thread [" << std::this_thread::get_id() << "]" << endl;
                continue; //return;
            }
        }
 
        //Gr8. store value now..
        //out << "Setter: thread [" << std::this_thread::get_id() << "] storing key value [" << key << ", " << value << "]" << endl;
        atomic_store_explicit(&m_entries[index].value, value, memory_order_relaxed);
        return;
    }
}

/* You might argue that in getItem, we need some kind of a data dependency (LoadLoad barrier), otherwise
 * because we are using relaxed memory order constraints, the value may be fetched ahead of the key, creating a kind
 * of "Out Of Air" thin store issue you read about earlier. However, the C++11 standard now prevents it from happening.
 *
 * It explicitly states, that
 * Compiler transformations that introduce assignments to a potentially shared memory location that would not be modified
 * by the abstract machine are generally precluded by this standard.
 */
        
int32_t ArrayOfItems::getItem(int32_t key) const
{
    assert(key != 0);
    //First iterator linearly through the array and search for key
    for(uint32_t index = 0; index < m_size; ++index)
    {
        int32_t probedKey = atomic_load_explicit(&m_entries[index].key, memory_order_relaxed);
        if(probedKey == key)
        {
            int32_t probedValue = atomic_load_explicit(&m_entries[index].value, memory_order_relaxed);
            //out << "Getter: thread [" << std::this_thread::get_id() << "], key value [" << probedKey << ", " << probedValue << "]" <<  endl;
            return probedValue;
        }
        else if (probedKey == 0)
        {
            //out << "Getter: thread [" << std::this_thread::get_id() << "], key [" << probedKey << "]" <<  endl;
            return 0;
        }
    }
    return 0;
}

uint32_t ArrayOfItems::getItemCount() const
{
    uint32_t index = 0;
    for(index = 0; index < m_size; ++index)
    {
        if((atomic_load_explicit(&m_entries[index].key, memory_order_relaxed) == 0) ||
           (atomic_load_explicit(&m_entries[index].value, memory_order_relaxed) == 0)) 
        return index;
    }
    return index + 1;
}

