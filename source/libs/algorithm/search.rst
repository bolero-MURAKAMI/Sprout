.. _sprout-algorithm-search:

###############################################################################
search
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator1, typename ForwardIterator2>
  inline SPROUT_CONSTEXPR ForwardIterator1
  search(
    ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2
    );

  template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR ForwardIterator1
  search(
    ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2,
    BinaryPredicate pred
    );

Effects
========================================

| Finds a subsequence of equal values in a sequence.

Returns
========================================

| The first iterator i in the range [first1,last1 - (last2-first2)) such that for any nonnegative integer n less than ``last2 - first2`` the following corresponding conditions hold: ``*(i + n) == *(first2 + n)``, ``pred(*(i + n), *(first2 + n))``.
| Returns first1 if [first2,last2) is empty, otherwise returns last1 if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/search.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 3>{{3, 4, 5}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::search(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result != end(input1), "found a subsequence equal to input2 from input1.");
  static_assert(result - begin(input1) == 2, "a found position is 2.");

Complexity
========================================

| At most ``(last1 - first1) * (last2 - first2)`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/search.hpp``
| Convenience header: ``sprout/algorithm.hpp``

