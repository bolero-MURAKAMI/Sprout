.. _sprout-algorithm-none_of_equal:
###############################################################################
none_of_equal
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename T>
  inline SPROUT_CONSTEXPR bool
  none_of_equal(InputIterator first, InputIterator last, T const& value);

Returns
========================================

*true* if [first,last) is empty or if ``*i == value`` is false for every iterator i in the range [first,last), and *false* otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/none_of_equal.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::none_of_equal(begin(input), end(input), 11);
  static_assert(result, "none of input is equal to 11.");

Complexity
========================================

At most ``last - first`` applications of the predicate.

Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

``sprout/algorithm/none_of_equal.hpp``

Convenience header: ``sprout/algorithm.hpp``

