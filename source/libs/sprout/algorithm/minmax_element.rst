.. _sprout-algorithm-minmax_element:
###############################################################################
minmax_element
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ForwardIterator>
  inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
  minmax_element(ForwardIterator first, ForwardIterator last);
  
  template<typename ForwardIterator, typename Compare>
  inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
  minmax_element(ForwardIterator first, ForwardIterator last, Compare comp);

Returns
========================================

| ``make_pair(first, first)`` if [first,last) is empty, otherwise ``make_pair(m, M)``, where m is the first iterator in [first,last) such that no iterator in the range refers to a smaller element, and where M is the last iterator in [first,last) such that no iterator in the range refers to a larger element.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/minmax_element.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::minmax_element(begin(input), end(input));
  static_assert(*result.first == 1, "a min element is 1.");
  static_assert(*result.second == 10, "a max element is 10.");
  static_assert(result.first - begin(input) == 0, "a min element position is 0.");
  static_assert(result.second - begin(input) == 9, "a max element position is 9.");

Complexity
========================================

| At most ``max(floor((3/2)*(N - 1)), 0)`` applications of the corresponding predicate, where N is ``distance(first, last)``.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/minmax_element.hpp``
| Convenience header: ``sprout/algorithm.hpp``

