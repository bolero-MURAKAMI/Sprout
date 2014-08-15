.. _sprout-algorithm-count:

###############################################################################
count
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename T>
  inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
  count(InputIterator first, InputIterator last, T const& value);

Returns
========================================

| The number of iterators i in the range [first,last) for which the following corresponding conditions hold: ``*i == value``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/count.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::count(begin(input), end(input), 5);
  static_assert(result == 4, "counted 4 elements equal to 5 from input.");

Complexity
========================================

| Exactly ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/count.hpp``
| Convenience header: ``sprout/algorithm.hpp``

