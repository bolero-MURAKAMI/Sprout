.. _sprout-algorithm-all_of_equal:
###############################################################################
all_of_equal
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename T>
  inline SPROUT_CONSTEXPR bool
  all_of_equal(InputIterator first, InputIterator last, T const& value);

Returns
========================================

*true* if [first,last) is empty or if ``*i == value`` is true for every iterator i in the range [first,last), and *false* otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/all_of_equal.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::all_of_equal(begin(input), end(input), 1);
  static_assert(result, "all of input is equal to 1.");

Complexity
========================================

At most ``last - first`` applications of the predicate.

Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

``sprout/algorithm/all_of_equal.hpp``

Convenience header: ``sprout/algorithm.hpp``

