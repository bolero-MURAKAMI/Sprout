.. _sprout-algorithm-equal_range:

###############################################################################
equal_range
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator, typename T>
  inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
  equal_range(ForwardIterator first, ForwardIterator last, T const& value);
  
  template<typename ForwardIterator, typename T, typename Compare>
  inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
  equal_range(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

Requires
========================================

| The elements e of [first,last) shall be partitioned with respect to the expressions ``e < value`` and ``!(value < e)`` or ``comp(e, value)`` and ``!comp(value, e)``.
| Also, for all elements e of [first, last), ``e < value`` shall imply ``!(value < e)`` or ``comp(e, value)`` shall imply ``!comp(value, e)``.

Returns
========================================

| ``make_pair(lower_bound(first, last, value), upper_bound(first, last, value))``
| or
| ``make_pair(lower_bound(first, last, value, comp), upper_bound(first, last, value, comp))``

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/equal_range.hpp>
  #include <sprout/algorithm/all_of_equal.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::equal_range(begin(input), end(input), 5);
  static_assert(result.first - begin(input) == 3, "a lower bound position is 3.");
  static_assert(result.second - begin(input) == 7, "a upper bound position is 7.");
  static_assert(sprout::all_of_equal(result.first, result.second. 5), "all of result range is equal to 5.");

Complexity
========================================

| At most ``2 * log2(last - first) + O(1)`` comparisons.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/equal_range.hpp``
| Convenience header: ``sprout/algorithm.hpp``

