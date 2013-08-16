.. _sprout-algorithm-one_of:
###############################################################################
one_of
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename Predicate>
  inline SPROUT_CONSTEXPR bool
  one_of(InputIterator first, InputIterator last, Predicate pred);

Returns
========================================

*true* if [first,last) is not empty and there is only one iterator i in the range [first,last) such that ``pred(*i)`` is true, and *false* otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/one_of.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  #include <sprout/functional.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::one_of(begin(input), end(input), bind2nd(greater<>(), 9));
  static_assert(result, "one of input is greater than 9.");

Complexity
========================================

At most ``last - first`` applications of the predicate.

Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

``sprout/algorithm/one_of.hpp``

Convenience header: ``sprout/algorithm.hpp``

