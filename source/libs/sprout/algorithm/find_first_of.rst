.. _sprout-algorithm-find:
###############################################################################
find_first_of
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator1, typename ForwardIterator2>
  inline SPROUT_CONSTEXPR InputIterator1
  find_first_of(
  	InputIterator1 first1, InputIterator1 last1,
  	ForwardIterator2 first2, ForwardIterator2 last2
  	);
  
  template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
  inline SPROUT_CONSTEXPR InputIterator1
  find_first_of(
  	InputIterator1 first1, InputIterator1 last1,
  	ForwardIterator2 first2, ForwardIterator2 last2,
  	BinaryPredicate pred
  	);

Effects
========================================

| Finds an element that matches one of a set of values.

Returns
========================================

| The first iterator i in the range [first1,last1) such that for some iterator j in the range [first2,last2) the following conditions hold: ``*i == *j``, ``pred(*i,*j)``.
| Returns last1 if [first2,last2) is empty or if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/find_first_of.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 3>{{3, 4, 5}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::find_first_of(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result != end(input1), "found an element equal to an one of input2 from input1.");
  static_assert(result - begin(input1) == 2, "a found position is 2.");

Complexity
========================================

| At most ``(last2 - first2) * (last1 - first1 - (last2 - first2) + 1)`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/find_first_of.hpp``
| Convenience header: ``sprout/algorithm.hpp``

