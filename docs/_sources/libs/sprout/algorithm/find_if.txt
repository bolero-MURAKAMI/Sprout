.. _sprout-algorithm-find_if:
###############################################################################
find_if
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename Predicate>
  inline SPROUT_CONSTEXPR InputIterator
  find_if(InputIterator first, InputIterator last, Predicate pred);

Returns
========================================

| The first iterator i in the range [first,last) for which the following corresponding conditions hold: ``pred(*i)``.
| Returns last if no such iterator is found.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/find_if.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  #include <sprout/functional.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::find_if(begin(input), end(input), bind2nd(greater<>(), 7));
  static_assert(result != end(input), "found a element greater than 7 from input.");
  static_assert(*result == 8, "a found iterator is pointing to 8.");

Complexity
========================================

| At most ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/find_if.hpp``
| Convenience header: ``sprout/algorithm.hpp``

