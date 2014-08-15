.. _sprout-algorithm-is_sorted:

###############################################################################
is_sorted
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR bool
  is_sorted(ForwardIterator first, ForwardIterator last);
  
  template<typename ForwardIterator, typename Compare>
  inline SPROUT_CONSTEXPR bool
  is_sorted(ForwardIterator first, ForwardIterator last, Compare comp);

Returns
========================================

| ``is_sorted_until(first, last) == last``, ``is_sorted_until(first, last, comp) == last``

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_sorted.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_sorted(begin(input), end(input));
  static_assert(result, "input is sorted.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_sorted.hpp``
| Convenience header: ``sprout/algorithm.hpp``

