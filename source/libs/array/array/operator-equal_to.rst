.. _sprout-array-array-operator-equal_to:
###############################################################################
operator==
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR bool
  operator==(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs);

Returns
========================================

| true if the contents of the containers are equivalent, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto y = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(x == y, "x is equal to y.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/array/comparison.hpp``
| Convenience header: ``sprout/array.hpp``

