.. _sprout-algorithm-find:
###############################################################################
find
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename T>
  inline SPROUT_CONSTEXPR InputIterator
  find(InputIterator first, InputIterator last, T const& value);

Returns
========================================

| The first iterator i in the range [first,last) for which the following corresponding conditions hold: ``*i == value``.
| Returns last if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/find.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::find(begin(input), end(input), 8);
  static_assert(result != end(input), "found a element equal to 8 from input.");
  static_assert(result - begin(input1) == 7, "a found position is 7.");

Complexity
========================================

| At most ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/find.hpp``
| Convenience header: ``sprout/algorithm.hpp``

