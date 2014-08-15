.. _sprout-algorithm-equal:

###############################################################################
equal
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR bool
  equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred);
  
  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR bool
  equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);
  
  template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR bool
  equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred);
  
  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR bool
  equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);

Remarks
========================================

| If last2 was not given in the argument list, it denotes ``first2 + (last1 - first1)`` below.

Returns
========================================

| If ``last1 - first1 != last2 - first2``, return false.
| Otherwise return true if for every iterator i in the range [first1,last1) the following corresponding conditions hold: ``*i == *(first2 + (i - first1))``, ``pred(*i, *(first2 + (i - first1)))``.
| Otherwise, returns false.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/equal.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result, "input2 equals to input1.");

Complexity
========================================

| No applications of the corresponding predicate if InputIterator1 and InputIterator2 meet the requirements of random access iterators and ``last1 - first1 != last2 - first2``.
| Otherwise, at most ``min(last1 - first1, last2 - first2)`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/equal.hpp``
| Convenience header: ``sprout/algorithm.hpp``

