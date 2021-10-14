/*
 * template <typename ExecutionPolicy, typename It, typename T, typename BinaryOp>
 * std::reduce(ExecutionPolicy, Iter first, Iter end, T init, BinaryOp op)
 * basically this algorithm works like std::accumulate
 *
 * std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 * std::accumulate(v.begin(), v.end(), 0) ; returns "55", ie simply add all elements sequentially. This is because default
 * BinaryOp is std::plus<>{}. Same way for std::reduce also, default BinaryOp is std::plus<>{}. The difference is that std::reduce
 * performs a kind of divide and conquer. so may be a[0] + a[1] is calculated separately, then a[2]+a[3]. and so on.
 * so with execution policy of par and par_unseq, std::reduce() should beat std::accumulate(). However note that your binaryOp should
 * be associative and transitive, otherwise results from this algo would be non-deterministic.
 *
 * commutative means x + y = y + x
 * associative means x + (y+z) = (x+y) + z
 *
 * similarly we have std::transform_reduce() which can transform your element before it gets reduced. Example:
 * std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 * std::transform_reduce(
 *  std::execution::par,
 *  begin(v),
 *  end(v),
 *  0,
 *  std::plus<int>{},
 *  [](const int& val) { return val * 2; }
 *  ); // will return 110.
 */

int main() {

}
