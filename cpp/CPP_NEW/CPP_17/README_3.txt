What is a range based for loop equivalent to?

for (for-range-declaration : for-range-initializer)
    statement;

 is equivalent to

 auto&& __range = for-loop-initializer
 auto __begin = begin-expr;
 auto __end = end-expr;
 for(; __begin != __end; ++__begin) {
     for-range-declaration = *__begin;
     statement;
 }