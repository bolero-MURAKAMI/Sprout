.. _sprout-algorithm-is_increasing:

###############################################################################
is_increasing
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR bool
  is_increasing(ForwardIterator first, ForwardIterator last);

Returns
========================================

| Same as ``is_sorted(first, last, less<>())``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_increasing.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_increasing(begin(input), end(input));
  static_assert(result, "input is increasing.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_increasing.hpp``
| Convenience header: ``sprout/algorithm.hpp``

