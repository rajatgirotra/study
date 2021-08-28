#pragma once
#include <functional>

/* Many times you'll encounter that for a user defined key, the hash has to computed from the combination of multiple data
 * members of your class. For example, for a
 * struct Key {
 *     string firstname;
 *     string lastname;
 *     };
 *  the hash should be a combination of hashes of both first and last name. For such a case how do we combine them.
 *  Well, for such a case we just copy how boost does it.
 *
 *  seed = 0;
 *  seed ^= std::hash<T>(value) + 0x9E3779B9 + (seed<<6) + (seed>>2); // basically an XOR.
 *
 *  We can generalize this concept and create a variadic template version of a hash combiner as shown below.
 */

namespace hash_combiner {
    template <typename...> struct hash; // a variadic hash template definition.

    // end of recursion case, create a specialization for template<typename T>
    template <typename T>
    struct hash<T> : std::hash<T> {};

    // general case
    template <typename T, typename... Rest>
    struct hash<T, Rest...> {
        inline std::size_t operator()(const T& value, const Rest&... rest) const noexcept {
            // recursively compute hash
            std::size_t seed = hash<Rest...>{}(rest...);
            seed ^= hash<T>{}(value) + 0x9E3779B9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };
}

/* Let's use it next in hash_map_create.cpp */
