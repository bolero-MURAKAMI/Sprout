.. _sprout-algorithm-tristate_lexicographical_compare:
###############################################################################
tristate_lexicographical_compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR int
  tristate_lexicographical_compare(
  	InputIterator1 first1, InputIterator1 last1,
  	InputIterator2 first2, InputIterator2 last2
  	);
  
  template<typename InputIterator1, typename InputIterator2, typename Compare>
  inline SPROUT_CONSTEXPR int
  tristate_lexicographical_compare(
  	InputIterator1 first1, InputIterator1 last1,
  	InputIterator2 first2, InputIterator2 last2,
  	Compare comp
  	);

Returns
========================================

| A value less than zero if the sequence of elements defined by the range [first1,last1) is lexicographically less than the sequence of elements defined by the range [first2,last2) and false otherwise.
| A value greater than zero if the sequence of elements defined by the range [first1,last1) is lexicographically greater than the sequence of elements defined by the range [first2,last2) and false otherwise.
| Otherwise, returns a zero value.

Remarks
========================================

| If two sequences have the same number of elements and their corresponding elements are equivalent, then neither sequence is lexicographically less than the other.
| If one sequence is a prefix of the other, then the shorter sequence is lexicographically less than the longer sequence.
| Otherwise, the lexicographical comparison of the sequences yields the same result as the comparison of the first corresponding pair of elements that are not equivalent.

| An empty sequence is lexicographically less than any non-empty sequence, but not less than any empty sequence.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/tristate_lexicographical_compare.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 11, 12, 13}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result < 0, "input1 < input2 by lexicographical comparison.");

Complexity
========================================

| At most ``2*min((last1 - first1), (last2 - first2)) + O(1)`` applications of the corresponding comparison.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/tristate_lexicographical_compare.hpp``
| Convenience header: ``sprout/algorithm.hpp``

