.. _sprout-algorithm-search_n:

###############################################################################
search_n
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator, typename Size, typename T>
  inline SPROUT_CONSTEXPR ForwardIterator
  search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value);
  
  template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR ForwardIterator
  search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value, BinaryPredicate pred);

Requires
========================================

| The type Size shall be convertible to integral type.

Effects
========================================

| Finds a subsequence of equal values in a sequence.

Returns
========================================

| The first iterator i in the range [first,last-count) such that for any non-negative integer n less than count the following corresponding conditions hold: ``*(i + n) == value``, ``pred(*(i + n),value)``.
| Returns last if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/search_n.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::search_n(begin(input1), end(input1), 4, 5);
  static_assert(result != end(input1), "found a subsequence equal to 4 values of 5 from input1.");
  static_assert(result - begin(input1) == 3, "a found position is 3.");

Complexity
========================================

| At most ``last - first`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/search_n.hpp``
| Convenience header: ``sprout/algorithm.hpp``

