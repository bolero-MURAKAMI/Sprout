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
  
  // delimiter version
  template<typename InputIterator1, typename T1, typename InputIterator2, typename T2>
  inline SPROUT_CONSTEXPR int
  tristate_lexicographical_compare(
    InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
    InputIterator2 first2, InputIterator2 last2, T2 const& delim2
    );
  
  template<typename InputIterator1, typename T1, typename InputIterator2, typename T2, typename Compare>
  inline SPROUT_CONSTEXPR int
  tristate_lexicographical_compare(
    InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
    InputIterator2 first2, InputIterator2 last2, T2 const& delim2,
    Compare comp
    );

Returns
========================================

| A value less than zero if the sequence of elements defined by the range [first1,last1) is lexicographically less than the sequence of elements defined by the range [first2,last2).
| Otherwise, a value greater than zero if the sequence of elements defined by the range [first1,last1) is lexicographically greater than the sequence of elements defined by the range [first2,last2).
| Otherwise, returns a zero value.

| If the delimiter version, last1 and last2 the following corresponding transformations: ``find_if(first1, last1, bind2nd(equiv(), delim1))`` and ``find_if(first2, last2, bind2nd(equiv(), delim2))``, ``find_if(first1, last1, bind2nd(equiv(comp), delim1))`` and ``find_if(first2, last2, bind2nd(equiv(comp), delim2))``.

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
  SPROUT_STATIC_CONSTEXPR auto input2 = array<int, 10>{{1, 2, 3, 4, 5, 10, 9, 8, 7, 6}};
  SPROUT_STATIC_CONSTEXPR auto result1 = sprout::tristate_lexicographical_compare(begin(input1), end(input1), begin(input2), end(input2));
  SPROUT_STATIC_CONSTEXPR auto result2 = sprout::tristate_lexicographical_compare(begin(input1), end(input1), 10, begin(input2), end(input2), 10);
  static_assert(result1 < 0, "input1 < input2 by lexicographical comparison.");
  static_assert(result2 > 0, "input1 < input2 by lexicographical comparison(delimited by 10).");

Complexity
========================================

| At most ``2*min((last1 - first1), (last2 - first2)) + O(1)`` applications of the corresponding comparison.
| At most ``6*min((last1 - first1), (last2 - first2)) + O(1)`` applications of the corresponding comparison for delimiter version.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/tristate_lexicographical_compare.hpp``
| Convenience header: ``sprout/algorithm.hpp``

