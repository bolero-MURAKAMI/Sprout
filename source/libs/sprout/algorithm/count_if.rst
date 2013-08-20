.. _sprout-algorithm-count_if:
###############################################################################
count_if
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator, typename Predicate>
  inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
  count_if(InputIterator first, InputIterator last, Predicate pred);

Returns
========================================

| The number of iterators i in the range [first,last) for which the following corresponding conditions hold: ``pred(*i)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/count_if.hpp>
  #include <sprout/array.hpp>
  #include <sprout/container.hpp>
  #include <sprout/functional.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::count_if(begin(input), end(input), bind2nd(modulus<>(), 2));
  static_assert(result == 5, "counted 5 elements of odd number from input.");

Complexity
========================================

| Exactly ``last - first`` applications of the predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/count_if.hpp``
| Convenience header: ``sprout/algorithm.hpp``

