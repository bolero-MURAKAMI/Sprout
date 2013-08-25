.. _sprout-algorithm-lexicographical_compare:
###############################################################################
lexicographical_compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator1, typename InputIterator2>
  inline SPROUT_CONSTEXPR bool
  lexicographical_compare(
    InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2
    );
  
  template<typename InputIterator1, typename InputIterator2, typename Compare>
  inline SPROUT_CONSTEXPR bool
  lexicographical_compare(
    InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2,
    Compare comp
    );

Returns
========================================

| true if the sequence of elements defined by the range [first1,last1) is lexicographically less than the sequence of elements defined by the range [first2,last2) and false otherwise.

Remarks
========================================

| If two sequences have the same number of elements and their corresponding elements are equivalent, then neither sequence is lexicographically less than the other.
| If one sequence is a prefix of the other, then the shorter sequence is lexicographically less than the longer sequence.
| Otherwise, the lexicographical comparison of the sequences yields the same result as the comparison of the first corresponding pair of elements that are not equivalent.

.. sourcecode:: c++

  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
      if (*first1 < *first2) return true;
      if (*first2 < *first1) return false;
  }
  return first1 == last1 && first2 != last2;

| An empty sequence is lexicographically less than any non-empty sequence, but not less than any empty sequence.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/lexicographical_compare.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 11, 12, 13}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::lexicographical_compare(begin(input1), end(input1), begin(input2), end(input2));
  static_assert(result, "input1 < input2 by lexicographical comparison.");

Complexity
========================================

| At most ``2*min((last1 - first1), (last2 - first2))`` applications of the corresponding comparison.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/lexicographical_compare.hpp``
| Convenience header: ``sprout/algorithm.hpp``

