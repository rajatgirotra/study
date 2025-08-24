#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor.hpp>
#include <iostream>
#include <string>
using namespace std;

#define VAR_NAME(x) BOOST_PP_CAT(my_var_, x)

#define PRINT(z, n, text) std::cout << text << n << '\n';

#define MY_SEQ (10)(20)(30)
#define PRINT_ELEM(z, data, elem) std::cout << elem << '\n';

#define STR(x) #x
#define NAME rajat
#define EXPAND_BEFORE_STRINGIZE(x) BOOST_PP_STRINGIZE(x)

# define ANOTHER_SEQ (a)(b)(c)
#define CALL_NESTED(r, data, elem) \
    std::cout << #data << elem << "\n"; \
    BOOST_PP_SEQ_FOR_EACH_R(r, PRINT_ELEM, _, ANOTHER_SEQ); // output will be 10 followed by a, b, c. then 20 followed by a,b,c and so on.

int main() {
    // BOOST_PP_CAT
    [[maybe_unused]] int VAR_NAME(1) = 10;
    cout << VAR_NAME(1) << endl;

    /*
     * BOOST_PP_REPEAT(count, MACRO, data)
     * i.e. call MACRO count times and supply data to it on each iteration.
     * Under the hood, BOOST_PP_REPEAT calls your MACRO with 3 arguments.
     * 1. z --> an internal iteration depth counter (mostly this is ignored)
     * 2. n --> the current iteration number (0..n-1)
     * 3. data --> the value you passed as the third argument.
     */
    BOOST_PP_REPEAT(5, PRINT, "Value: ")

    /*
     * in Boost PP, a sequence is not like a vector or deque. a sequence is a collection of tokens
     * inside round brackets. like (10)(20)(30)
     * BOOST_PP_SEQ_FOR_EACH(MACRO, data, SEQ) calls your macro as many times as the number of elements
     * in the sequence, together with the data.
     *
     * Your macro must be defined as MACRO(z, data, elem_in_seq) where
     * 1. z --> an internal iteration depth counter (mostly this is ignored)
     * 2. data --> the value you passed as the third argument.
     * 3. elem_in_seq --> the element in seq
     */
    BOOST_PP_SEQ_FOR_EACH(PRINT_ELEM, _, MY_SEQ)

    /*
     * Note that BOOST_PP_SEQ_FOR_EACH is not reentrant. so you can't have the macro which BOOST_PP_SEQ_FOR_EACH calls also expand using BOOST_PP_SEQ_FOR_EACH.
     * If you want to  that you have to use BOOST_PP_SEQ_FOR_EACH_R
     */
    BOOST_PP_SEQ_FOR_EACH_R(0, PRINT_ELEM, _, MY_SEQ)

    /*
     * BOOST_PP_STRINGIZE
     * this macro converts its argument to a literal string.
     */
    cout << STR(NAME) << endl; // note how this stops the moment it gets a string literal "NAME"
    cout << BOOST_PP_STRINGIZE(NAME) << endl;

    // Very Important note: BOOST_PP_STRINGIZE() is a very convenient way to debug the output of any macro
    cout << BOOST_PP_STRINGIZE(BOOST_PP_REPEAT(5, PRINT, "Value: ")) << endl;

    // another use case for STRINGIZE
    // also demonstrates BOOST_PP_SEQ_ENUM which is very trivial
#define SQL_FIELDS (id)(name)(email)

    const char* query = BOOST_PP_STRINGIZE(
        SELECT BOOST_PP_SEQ_ENUM(SQL_FIELDS) from users;
        );

    cout << "query: "  << query << endl;

// insert a comma followed by field for all fields except the first one
#define FIELD_DEF(z, data, index, field) \
    BOOST_PP_IF(index, BOOST_PP_COMMA, BOOST_PP_EMPTY)()field // insert comma only if i > 0

    const char* query1 = BOOST_PP_STRINGIZE(
    SELECT BOOST_PP_SEQ_FOR_EACH_I(FIELD_DEF, _, SQL_FIELDS) from users;
    );
    cout << "query: "  << query1 << endl;

    // insert a comma followed by field for all fields except the first one
    // 3rd way
#define FIELD_DEF2(z, data, index, field) \
    field BOOST_PP_IF(BOOST_PP_EQUAL(index, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SQL_FIELDS))), BOOST_PP_EMPTY, BOOST_PP_COMMA)() // insert comma only if i > 0

    const char* query2 = BOOST_PP_STRINGIZE(
    SELECT BOOST_PP_SEQ_FOR_EACH_I(FIELD_DEF2, _, SQL_FIELDS) from users;
    );
    cout << "query: "  << query2 << endl;

    /*
     * Just like (10)(20)(30) is a sequence, (10 20 30), (a b) are  tuples. There are macro's available for both SEQ and TUPLE processing.
     */

#define OP(a, b) (a b)
#define MACRO(n) BOOST_PP_IF(n, OP, BOOST_PP_TUPLE_EAT())(1, 2)

    cout << "Nothing: " << BOOST_PP_STRINGIZE(MACRO(0)) << endl; // expands to nothing
    cout << BOOST_PP_STRINGIZE(MACRO(1)) << endl; // expands to (1, 2)

#define TUPLE (B, O, O, S, T)
    cout << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, TUPLE)) << endl;
    cout << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, TUPLE)) << endl;
    cout << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ENUM(TUPLE)) << endl;
}

/* please read 1_README.txt next */