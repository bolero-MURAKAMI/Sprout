.. _sprout-algorithm-all_of:
###############################################################################
all_of
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename Predicate>
  inline SPROUT_CONSTEXPR bool
  all_of(InputIterator first, InputIterator last, Predicate pred);

Returns
========================================

| true if [first,last) is empty or if ``pred(*i)`` is true for every iterator i in the range [first,last), and false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/all_of.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  #include <sprout/functional.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::all_of(begin(input), end(input), bind2nd(less<>(), 11));
  static_assert(result, "all of input is less than 11.");

Complexity
========================================

| At most ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/all_of.hpp``
| Convenience header: ``sprout/algorithm.hpp``

