#include <unordered_map>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/* The definition of the unordered_map is very trivial.
 * template <typename Key,
 *           typename Value,
 *           typename Hash = std::hash<Key>,
 *           typename Equal = std::equal_to<Key>,
 *           typename Allocator = std::allocator<std::pair<const Key, Value>>>
 * class unordered_map{};
 *
 * unordered_map has the following important typedef
 *
 * using key_type = Key;
 * using mapped_type = Value;
 * using value_type = std::pair<const Key, Value>;
 * using difference_type = std::size_t;
 * and others.
 *
 * In an ordered_map or unordered_set, key/values are organized in buckets.
 * the default value of bucket_count is implementation defined.
 *
 * The Hash template parameter is a function object as you saw in Must_Read_1.txt.This hash function object takes a key
 * and returns a hash value which is used to compute the bucket number into which to put the element. If different keys produce
 * the same hash, then it is a hash collision (which is not a good thing). In hash collision the Equal function object is used
 * to find the correct value for the given key.
 *
 * The important functions dealing with buckets and load factor are shown below.
 * We also specify which functions can get the map to rehash everything.
 */

int main() {
    std::unordered_map<string, string> hashMap;

    cout << "hashMap bucket count: " << hashMap.bucket_count() << endl;
    cout << "hashMap max bucket count: " << hashMap.max_bucket_count() << endl;
    cout << "hashMap load factor: " << hashMap.load_factor() << endl;

    /* load factor is just (total_elements/total_buckets). ie an average of the number of elements per bucket.
     * the load factor does not tell how the elements are distributed inside the buckets.
     */

    cout << "hashMap max load factor: " << hashMap.max_load_factor() << endl;
    // if this value is reached. it will cause a rehash. default is 1 on most platforms. ie there is more than 1 element
    // in every bucket ON AVERAGE, do a rehash. Normally, a value of 0.75 is used as the max_load_factor.
    hashMap.max_load_factor(0.75);
    cout << "hashMap max load factor (new value): " << hashMap.max_load_factor() << endl;

    string h {"Hello"};
    cout << "hash of string Hello: " << std::hash<std::string>{}(h) << ", bucket id: " << hashMap.bucket(h) << endl;
    // bucket() returns the bucket id where an element will be stored.

    // rehash function
    hashMap.rehash(25); // 25 is the new bucket count.
    cout << "hashMap bucket count (after rehashing): " << hashMap.bucket_count() << endl;

    // iterator invalidation
    // functions like clear(), rehash(), operator=(), reserve() will always cause iteration invalidation
    // functions like insert(), emplace(), operator[] will only invalidate the iterator if it causes a rehash
    // erase will invalidate the iterator which is pointed to.
}

/* Lets see hash_combine.hpp next. Then we'll see how to construct and use hash maps in various ways */
