.. _sprout-array-array-operator-greater_equal:
###############################################################################
operator>=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR bool
  operator>=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs);

Returns
========================================

| true if the contents of the lhs are lexicographically greater than or equal the contents of rhs, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto y = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  static_assert(y >= x, "y is greater than or equal to x.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/array/comparison.hpp``
| Convenience header: ``sprout/array.hpp``

