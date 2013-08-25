.. _sprout-array-array-operator-subscript:
###############################################################################
operator[]
###############################################################################

Interface
========================================
.. sourcecode:: c++

  reference operator[](size_type n);
  
  SPROUT_CONSTEXPR const_reference operator[](size_type n) const;

Returns
========================================

| The element at the specified position in the array.

Remarks
========================================

| It causes undefined behavior if n is out of bounds.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(input[5] == 6, "an element at position 5 is 6.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

