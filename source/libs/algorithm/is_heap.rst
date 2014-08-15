.. _sprout-algorithm-is_heap:

###############################################################################
is_heap
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename RandomAccessIterator>
  inline SPROUT_CONSTEXPR bool
  is_heap(RandomAccessIterator first, RandomAccessIterator last);
  
  template<typename RandomAccessIterator, typename Compare>
  inline SPROUT_CONSTEXPR bool
  is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

Returns
========================================

| ``is_heap_until(first, last) == last``, ``is_heap_until(first, last, comp) == last``

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_heap.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(begin(input), end(input));
  static_assert(result, "input is a heap.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_heap.hpp``
| Convenience header: ``sprout/algorithm.hpp``

