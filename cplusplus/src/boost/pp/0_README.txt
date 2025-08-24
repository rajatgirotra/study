Boost PP is very trivial. It is just C++ macros on steroids. It is a set of macros that extend the C preprocessor so you can:

1. Loop (BOOST_PP_REPEAT)
2. Count (BOOST_PP_SEQ_SIZE and BOOST_PP_VARIADIC_SIZE)
3. Concatenate tokens (BOOST_PP_CAT)
4. Generate code from lists/sequences (BOOST_PP_SEQ_FOR_EACH)
5. Do conditional logic (BOOST_PP_IF, BOOST_PP_EQUAL)
6. Do arithmetic (BOOST_PP_ADD, BOOST_PP_SUB)