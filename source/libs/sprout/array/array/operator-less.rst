.. _sprout-array-array-operator-less:
###############################################################################
operator<
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR bool
  operator<(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs);

Returns
========================================

| true if the contents of the lhs are lexicographically less than the contents of rhs, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto y = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  static_assert(x < y, "x is less than y.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/array/comparison.hpp``
| Convenience header: ``sprout/array.hpp``

