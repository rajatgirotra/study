/* 
 Before reading this please read
 remove_extent.cpp &
 fusion_extension.cpp
*/

#pragma once

/* What all things can/should we serialize
1) Any primitive type: int, double, bool, char, etc should be supported
2) An array type should be supported: int[], bool[] etc.
3) A container should be supported: vector<>, list<>, deque<>, set<>, map<>
4) A user defined type should be supported: Eg an employee class, a candidate class etc.
5) Any legitimate combination of the above.
So lets define a generic structure which we want to serialize.
*/

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <string>
#include <sstream>
#include <map>

namespace fusion = boost::fusion;
namespace mpl = boost::mpl;
using std::string;

// Forward declartion
template <typename T>
struct json_serializer;

/* Now we define serializers for each type that we need to support - primitive, array, containers, and user defined types */

// static function to indent depth as 3 spaces
static inline std::string tab(int depth) {
    std::string retVal = "";
    for (auto i = 0; i < depth; ++i) {
        retVal += "   ";
    }
    return retVal;
}


// primitive serializer
template <typename T>
struct primitive_serializer {
    typedef primitive_serializer<T> type;
    template <typename Ostream>
    static inline void serialize(Ostream& os, const T& value, int depth, bool array_value, bool pair) {
        // depth is used to pretty print the json. You may also choose to ignore it and print compressed json.
        // Very simple.
        if (array_value) {
            os << "\n" << tab(depth);
        }
        os << "\"" << value << "\"";
    }
};


// array serializer
template <typename T>
struct array_serializer {
    typedef array_serializer<T> type;

    typedef typename std::remove_extent<T>::type slice_t;
    static const size_t arr_size = sizeof(T)/sizeof(slice_t);

    template <typename Ostream>
    static inline void serialize(Ostream& os, const T& value, int depth, bool array_value, bool pair) {
        // Always start at new line to write an array.
        os << "\n" << tab(depth) << "[";

        for (auto i = 0; i < arr_size; ++i) {
            // serialize each element in the array
            json_serializer<slice_t>::serialize(os, value[i], depth+1, true, false);
            if (i != arr_size - 1) {
                os << ", ";
            }
        }
        os << "\n" << tab(depth) << "]";
    }
};

// container serializer
template <typename T>
struct container_serializer {
    typedef container_serializer<T> type;

    template <typename Ostream>
    static inline void serialize(Ostream& os, const T& value, int depth, bool array_value, bool pair) {
        const auto con_size = value.size();
        os << "\n" << tab(depth) << "[";
        size_t count = 0;
        for (const typename T::value_type& elem : value) {
            json_serializer<typename T::value_type>::serialize(os, elem, depth+1, true, false);
            if (count != con_size - 1) {
                os << ", ";
            }
            ++count;
        }
        os << "\n" << tab(depth) << "]";
    }
};

//specialize container_serializer for map
template <typename K, typename V, typename C, typename A>
struct container_serializer<std::map<K, V, C, A>> {
    typedef std::map<K, V, C, A> T;
    typedef container_serializer<T> type;

    template <typename Ostream>
    static inline void serialize(Ostream& os, const T& container, int depth, bool array_value, bool pair) {
        size_t size = container.size();
        size_t count = 0;

        os << "\n" << tab(depth) << "{";

        for (const typename T::value_type& p : container) {
            json_serializer<typename T::value_type>::serialize(os, p, depth+1, true, true);
            if (count != size - 1)
                os << ", ";
            ++count;
        }
        os << "\n" << tab(depth) << "}";
    }
};

template <typename S, typename N>
struct separator {
    static inline string comma() {
        return ", ";
    }
};

template <typename S>
struct separator<S, typename mpl::prior<fusion::result_of::size<S>>::type> {
    static inline string comma() {
        return "";
    }
};

/* After reading fusion_extension, you know how to get the variable name, type and value.
   That is exactly what we need here now. */
// S is a Fusion Sequence, N is an mpl integral constant
template <typename S, typename N>
struct struct_serializer_recursive {

    typedef typename fusion::result_of::value_at<S, N>::type current_t;
    typedef typename mpl::next<N>::type next_t;
    
    template <typename Ostream>
    static inline void serialize(Ostream& os, const S& s, int depth, bool array_value, bool pair) {
        // First get the name of the variable.
        string varName = fusion::extension::struct_member_name<S, N::value>::call();
        // get the value
        const auto& val = fusion::at<N>(s);

        // Output the key
        os << "\n" << tab(depth) << "\""
           << varName << "\" : ";

        // Recursively output the value
        json_serializer<current_t>::serialize(os, val, depth, false, false);

        // Add separater for next element
        os << separator<S, N>::comma();

        // recursively call this function
        struct_serializer_recursive<S, next_t>::serialize(os, s, depth, false, false);
    }
};

// End of above recursion
template <typename S>
struct struct_serializer_recursive<S, typename fusion::result_of::size<S>::type> {
    template <typename Ostream>
    static inline void serialize(Ostream& os, const S& s, int depth, bool array_value, bool pair) {
        // no-op
    }
};

// start of recursion
template <typename S>
struct struct_serializer_start : public struct_serializer_recursive<S, mpl::int_<0>> {
};

//pair serializer
template <typename S, typename N>
struct pair_serializer_recursive {

    template <typename Ostream>
    static inline void serialize(Ostream& os, const S& s, int depth, bool array_value, bool pair) {
        const auto& key = fusion::at<mpl::int_<0>>(s);
        os << "\n" << tab(depth) << "\"";
        os << key << "\" : ";

        pair_serializer_recursive<S, mpl::int_<1>>::serialize(os, s, depth, false, false);
    }
};

template <typename S>
struct pair_serializer_recursive<S, mpl::int_<1>> {
    template <typename Ostream>
    static inline void serialize(Ostream& os, const S& s, int depth, bool array_value, bool pair) {
        const auto& value = fusion::at<mpl::int_<1>>(s);
        os << "\"" << value << "\"";
    }
};

template <typename S>
struct pair_serializer_start : public pair_serializer_recursive<S, mpl::int_<0>> {
};

// struct serializer
template <typename T>
struct struct_serializer {
    typedef struct_serializer<T> type;
    template <typename Ostream>
    static inline void serialize(Ostream& os, const T& value, int depth, bool array_value, bool pair) {
        if (pair) {
            pair_serializer_start<T>::serialize(os, value, depth, false, false);
        } else {
            os << "\n" << tab(depth) << "{";
            struct_serializer_start<T>::serialize(os, value, depth+1, false, false);
            os << "\n" << tab(depth) << "}";
        }
    }
};

template <typename T>
struct choose_serializer {
    typedef typename mpl::eval_if<boost::is_array<T>,
                                  mpl::identity<array_serializer<T>>,
                                  typename mpl::eval_if<boost::spirit::traits::is_container<T>,
                                                        mpl::identity<container_serializer<T>>,
                                                        typename mpl::eval_if<boost::is_class<T>,
                                                                              mpl::identity<struct_serializer<T>>,
                                                                              mpl::identity<primitive_serializer<T>>
                                                                             >
                                                       >
                                  >::type type;
};

template <typename T>
struct json_serializer : public choose_serializer<T>::type {
};


template <typename T>
struct json {
    string to_json(void) {
       std::ostringstream os;
       json_serializer<T>::serialize(os << std::boolalpha, self(), 0, false, false);
       return os.str();
    }
 private:
    const T& self() const {
        return *static_cast<const T*>(this);
    }
};
