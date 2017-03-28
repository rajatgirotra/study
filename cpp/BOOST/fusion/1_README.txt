What is it?

Ok, one advantage that languages like Python, Lisp , Haskell have above C++ is heterogenous data structures.
C++ STL doesn't have that. So it introduced a powerful concept of tuple (available as Boost.Tuple and std::tuple in C++11).
However, as tuple became more popular, new usage patterns emerged for which there was no library of algorithms. Even Boost.Tuple allows
simple storing and retrieving tuple elements.

So fusion was invented which is a set of algorithms to work on heterogenous data sequences.
Boost fusion defines containers like list, vector, map, set and then provides functions (algorithms) which present VIEWS of the underlying data.
These VIEWS and containers are collectively called sequences in fusion.

Also fusion does lazy work and are non-sequence type preserving. This means that for example, if you apply a fusion algo transform() on a fusion sequence, then what you get is a
transform_view (the returned type may not be of the same class as the original sequence), which just holds a reference to the sequence and the transform function. Only when the returned view is later iterated,
the transform() gets applied. So fusion is suppose to be fast. It is modeled after MPL and STL.

Let's dive straight into it.
