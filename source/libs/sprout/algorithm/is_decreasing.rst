.. _sprout-algorithm-is_decreasing:
###############################################################################
is_decreasing
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR bool
  is_decreasing(ForwardIterator first, ForwardIterator last);

Returns
========================================

| Same as ``is_sorted(first, last, greater<>())``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_decreasing.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{5, 5, 4, 4, 3, 3, 2, 2, 1, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_decreasing(begin(input), end(input));
  static_assert(result, "input is decreasing.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_decreasing.hpp``
| Convenience header: ``sprout/algorithm.hpp``

