.. _sprout-algorithm-adjacent_find:
###############################################################################
adjacent_find
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR ForwardIterator
  adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred);
  
  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR ForwardIterator
  adjacent_find(ForwardIterator first, ForwardIterator last);

Returns
========================================

| The first iterator i such that both i and i + 1 are in the range [first,last) for which the following corresponding conditions hold: ``*i == *(i + 1)``, ``pred(*i, *(i + 1))``.
| Returns last if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/adjacent_find.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 5, 5, 6, 6, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::adjacent_find(begin(input), end(input));
  static_assert(result != end(input), "found adjacent elements equal to each other from input.");
  static_assert(result - begin(input) == 3, "a found position is 3.");

Complexity
========================================

| For a nonempty range, exactly ``min((i - first) + 1, (last - first) - 1)`` applications of the corresponding predicate, where i is adjacent_findÅfs return value.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/adjacent_find.hpp``
| Convenience header: ``sprout/algorithm.hpp``

