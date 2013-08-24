.. _sprout-algorithm-min_element:
###############################################################################
min_element
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR ForwardIterator
  min_element(ForwardIterator first, ForwardIterator last);
  
  template<typename ForwardIterator, typename Compare>
  inline SPROUT_CONSTEXPR ForwardIterator
  min_element(ForwardIterator first, ForwardIterator last, Compare comp);

Returns
========================================

| The first iterator i in the range [first,last) such that for any iterator j in the range [first,last) the following corresponding conditions hold: ``!(*j < *i)`` or ``!comp(*j, *i)``.
| Returns last if ``first == last``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/min_element.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(begin(input), end(input));
  static_assert(*result == 1, "a min element is 1.");
  static_assert(result - begin(input) == 0, "a min element position is 0.");

Complexity
========================================

| Exactly ``max((last - first) - 1, 0)`` applications of the corresponding comparisons.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/min_element.hpp``
| Convenience header: ``sprout/algorithm.hpp``

