.. _sprout-algorithm-any_of:
###############################################################################
any_of
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename Predicate>
  inline SPROUT_CONSTEXPR bool
  any_of(InputIterator first, InputIterator last, Predicate pred);

Returns
========================================

| *false* if [first,last) is empty or if there is no iterator i in the range [first,last) such that ``pred(*i)`` is true, and *true* otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/any_of.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  #include <sprout/functional.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::any_of(begin(input), end(input), bind2nd(greater<>(), 5));
  static_assert(result, "any of input is greater than 5.");

Complexity
========================================

| At most ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/any_of.hpp``
| Convenience header: ``sprout/algorithm.hpp``

