.. _sprout-array-array-rend:
###############################################################################
rend
###############################################################################

Interface
========================================
.. sourcecode:: c++

  reverse_iterator rend() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT;

Returns
========================================

| reverse iterator for position after the last element in reverse iteration.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(*(input.rend() - 1) == 1, "input last element of reverse iteration is 1.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

