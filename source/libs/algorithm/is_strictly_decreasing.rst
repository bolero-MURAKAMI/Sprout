.. _sprout-algorithm-is_strictly_decreasing:
###############################################################################
is_strictly_decreasing
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR bool
  is_strictly_decreasing(ForwardIterator first, ForwardIterator last);

Returns
========================================

| Same as ``is_sorted(first, last, greater_equal<>())``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_strictly_decreasing.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_decreasing(begin(input), end(input));
  static_assert(result, "input is strictly decreasing.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_strictly_decreasing.hpp``
| Convenience header: ``sprout/algorithm.hpp``

