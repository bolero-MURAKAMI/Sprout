.. _sprout-array-array-crend:

###############################################################################
crend
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT;

Returns
========================================

| reverse iterator for position after the last element in reverse iteration always const.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(*(input.crend() - 1) == 1, "input last element of reverse iteration is 1.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

