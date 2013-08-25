.. _sprout-array-array-size:
###############################################################################
size
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT;

Returns
========================================

| The number of elements contained in the array.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(input.size() == 10, "input size is 10.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

