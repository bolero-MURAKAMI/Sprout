.. _sprout-algorithm-lower_bound:

###############################################################################
lower_bound
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator, typename T>
  inline SPROUT_CONSTEXPR ForwardIterator
  lower_bound(ForwardIterator first, ForwardIterator last, T const& value);
  
  template<typename ForwardIterator, typename T, typename Compare>
  inline SPROUT_CONSTEXPR ForwardIterator
  lower_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

Requires
========================================

| The elements e of [first,last) shall be partitioned with respect to the expression ``e < value`` or ``comp(e, value)``.

Returns
========================================

| The furthermost iterator i in the range [first,last] such that for any iterator j in the range [first,i) the following corresponding conditions hold: ``*j < value`` or ``comp(*j, value)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/lower_bound.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::lower_bound(begin(input), end(input), 5);
  static_assert(result - begin(input) == 3, "a lower bound position is 3.");

Complexity
========================================

| At most ``log2(last - first) + O(1)`` comparisons.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/lower_bound.hpp``
| Convenience header: ``sprout/algorithm.hpp``

