.. _sprout-algorithm-is_strictly_increasing:

###############################################################################
is_strictly_increasing
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR bool
  is_strictly_increasing(ForwardIterator first, ForwardIterator last);

Returns
========================================

| Same as ``is_sorted(first, last, less_equal<>())``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_strictly_increasing.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(begin(input), end(input));
  static_assert(result, "input is strictly increasing.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_strictly_increasing.hpp``
| Convenience header: ``sprout/algorithm.hpp``

