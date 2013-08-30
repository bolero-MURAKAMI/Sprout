.. _sprout-array-array-swap:
###############################################################################
swap
###############################################################################

Interface
========================================
.. sourcecode:: c++

  void swap(array& y) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())));

Effects
========================================

| ``swap_ranges(begin(), end(), y.begin())``.

Throws
========================================

| Nothing unless one of the element-wise swap calls throws an exception.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  auto y = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  x.swap(y);
  SPROUT_ASSERT_MSG(x[0] = 10 && y[0] == 1, "each element are swapped.");

Complexity
========================================

| linear in N.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

