.. _sprout-algorithm-binary_search:

###############################################################################
binary_search
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator, typename T>
  inline SPROUT_CONSTEXPR bool
  binary_search(ForwardIterator first, ForwardIterator last, T const& value);
  
  template<typename ForwardIterator, typename T, typename Compare>
  inline SPROUT_CONSTEXPR bool
  binary_search(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

Requires
========================================

| The elements e of [first,last) are partitioned with respect to the expressions ``e < value`` and ``!(value < e)`` or ``comp(e, value)`` and ``!comp(value, e)``.
| Also, for all elements e of [first,last), ``e < value`` implies ``!(value < e)`` or ``comp(e, value)`` implies ``!comp(value, e)``.

Returns
========================================

| true if there is an iterator i in the range [first,last) that satisfies the corresponding conditions: ``!(*i < value) && !(value < *i)`` or ``comp(*i, value) && comp(value, *i)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/binary_search.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::binary_search(begin(input), end(input), 5);
  static_assert(result, "found 5 by binary search.");

Complexity
========================================

| At most ``log2(last - first) + O(1)`` comparisons.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/binary_search.hpp``
| Convenience header: ``sprout/algorithm.hpp``

