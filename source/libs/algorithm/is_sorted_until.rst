.. _sprout-algorithm-is_sorted_until:

###############################################################################
is_sorted_until
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR ForwardIterator
  is_sorted_until(ForwardIterator first, ForwardIterator last);
  
  template<typename ForwardIterator, typename Compare>
  inline SPROUT_CONSTEXPR ForwardIterator
  is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp);

Returns
========================================

| If ``distance(first, last) < 2``, returns last.
| Otherwise, returns the last iterator i in [first,last] for which the range [first,i) is sorted.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_sorted_until.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{6, 7, 8, 8, 10, 1, 2, 3, 4, 5}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_sorted_until(begin(input), end(input));
  static_assert(result - begin(input) == 5, "input is sorted until position 5.");

Complexity
========================================

| Linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_sorted_until.hpp``
| Convenience header: ``sprout/algorithm.hpp``

