.. _sprout-algorithm-is_permutation:

###############################################################################
is_permutation
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR bool
  is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred);
  
  template<typename ForwardIterator1, typename ForwardIterator2>
  inline SPROUT_CONSTEXPR bool
  is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2);
  
  template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR bool
  is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred);
  
  template<typename ForwardIterator1, typename ForwardIterator2>
  inline SPROUT_CONSTEXPR bool
  is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {

Remarks
========================================

| If last2 was not given in the argument list, it denotes ``first2 + (last1 - first1)`` below.

Returns
========================================

| If ``last1 - first1 != last2 - first2``, return false.
| Otherwise return true if there exists a permutation of the elements in the range [first2,first2 + (last1 - first1)), beginning with ForwardIterator2 begin, such that ``equal(first1, last1, begin)`` returns true or ``equal(first1, last1, begin, pred)`` returns true; otherwise, returns false.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/is_permutation.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{10, 9, 8, 1, 2, 3, 4, 5, 6, 7}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::is_permutation(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result, "input2 is a permutation of input1.");

Complexity
========================================

| No applications of the corresponding predicate if ForwardIterator1 and ForwardIterator2 meet the requirements of random access iterators and ``last1 - first1 != last2 - first2``.
| Otherwise, exactly distance(first1, last1) applications of the corresponding predicate if ``equal(first1, last1, first2, last2)`` would return true if pred was not given in the argument list or ``equal(first1, last1, first2, last2, pred)`` would return true if pred was given in the argument list; otherwise, at worst O(N^2), where N has the value ``distance(first1, last1)``.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/is_permutation.hpp``
| Convenience header: ``sprout/algorithm.hpp``

