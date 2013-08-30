.. _sprout-algorithm-is_heap_until:
###############################################################################
is_heap_until
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename RandomAccessIterator>
  inline SPROUT_CONSTEXPR RandomAccessIterator
  is_heap_until(RandomAccessIterator first, RandomAccessIterator last);
  
  template<typename RandomAccessIterator, typename Compare>
  inline SPROUT_CONSTEXPR RandomAccessIterator
  is_heap_until(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

Returns
========================================

| If ``distance(first, last) < 2``, returns last.
| Otherwise, returns the last iterator i in [first,last] for which the range [first,i) is a heap.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_heap_until.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 13, 14, 11}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap_until(begin(input), end(input));
  static_assert(result - begin(input) == 7, "input is a heap until position 7.");

Complexity
========================================

| Linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_heap_until.hpp``
| Convenience header: ``sprout/algorithm.hpp``

