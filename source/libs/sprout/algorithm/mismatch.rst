.. _sprout-algorithm-mismatch:
###############################################################################
mismatch
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
  mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred);
  
  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
  mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2;
  
  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
  mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);
  
  template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
  mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred);

Remarks
========================================

| If last2 was not given in the argument list, it denotes ``first2 + (last1 - first1)`` below.

Returns
========================================

| A pair of iterators i and j such that ``j == first2 + (i - first1)`` and i is the first iterator in the range [first1,last1) for which the following corresponding  conditions hold:
* j is in the range [first2,last2).
* ``!(*i == *(first2 + (i - first1)))``
* ``!pred(*i, *(first2 + (i - first1)))``
| Returns the pair ``first1 + min(last1 - first1, last2 - first2)`` and ``first2 + min(last1 - first1, last2 - first2)`` if such an iterator i is not found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/mismatch.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 10, 9, 8}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::mismatch(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result.first != end(input1) && result.second != end(input2), "input2 mismatches with input1.");
  static_assert(result.first - begin(input1) == 7, "a mismatched position is 7.");

Complexity
========================================

| At most ``last1 - first1`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/mismatch.hpp``
| Convenience header: ``sprout/algorithm.hpp``

