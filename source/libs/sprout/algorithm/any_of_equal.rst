.. _sprout-algorithm-any_of_equal:
###############################################################################
any_of_equal
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename T>
  inline SPROUT_CONSTEXPR bool
  any_of_equal(InputIterator first, InputIterator last, T const& value);

Returns
========================================

| *false* if [first,last) is empty or if there is no iterator i in the range [first,last) such that ``*i == value`` is true, and *true* otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/any_of_equal.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::any_of_equal(begin(input), end(input), 1);
  static_assert(result, "any of input is equal to 1.");

Complexity
========================================

| At most ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/any_of_equal.hpp``
| Convenience header: ``sprout/algorithm.hpp``

